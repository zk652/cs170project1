#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "problem.h"
#include <algorithm>
const int delta[4][2]{{-1,0},{0,-1},{1,0},{0,1}};// up, left,down,right
using namespace std;
struct State{
    State(const State& s){puzzle = s.puzzle;_width = s._width;_g = s._g;_h = s._h;}
    State(vector<vector<int>> p,int width,int g,int h = 0):puzzle(p),_width(width),_g(g),_h(h){}
    vector<vector<int>> puzzle;
    int _width;
    int _g;
    int _h;
    vector<int> get_blank_position(){
        for(int i = 0;i < puzzle.size();i++){
            for(int j = 0;j < puzzle.size();j++){
                if(puzzle[i][j] == 0){
                    return vector<int>{i,j};
                }
            }
        }
        return vector<int>{0,0};
    }
    void print_Puzzle(){
        for(int i = 0;i < _width;i++){
            for(int j = 0;j < _width;j++){
                std::cout << puzzle[i][j] << " ";
            }
            std::cout << "\n";
        }
    }
    bool operator==(const State& b){
        for(size_t i = 0;i < puzzle.size();i++){
            for(size_t j = 0;j < puzzle[0].size();j++){
                if(puzzle[i][j] != b.puzzle[i][j]){
                    return false;
                }
            }
        }
        return true;
    }
};
void choices_of_algorithm(){
    cout << "Enter your choice of algorithm\n";
    cout << "1. Uniform Cost Search.\n";
    cout << "2. A* with the Misplaced Tile heuristic.\n";
    cout << "3. A* with the Euclidean distance heruistic.\n";
}

bool Compare(const State a,const State b){
    int f1 = a._g + a._h;
    int f2 = b._g + b._h;
    return f1 > f2;
}

void Sort(vector<State> *states){
    sort(states->begin(),states->end(),Compare);
}

bool CheckVaildMove(int x,int y,int width){
    bool valid_x = (x >= 0 && x <= width-1);
    bool valid_y = (y >= 0 && y <= width-1);
    if(valid_x && valid_y){
        return true;
    }
    return false;
}
bool CheckCloseStates(const vector<State> &closeStates,State s){
    for(State i : closeStates){
        if(i == s){
            return true;
        }
    }
    return false;
}

int Misplaced_Tile_Heuristic(vector<vector<int>> current,vector<vector<int>> goal){
    int count = 0;
    for(int i = 0;i < current.size();i++){
        for(int j = 0;j < current[0].size();j++){
            if(current[i][j] != goal[i][j]){
                count++;
            }
        }
    }
    return count;
}

State child_state(const State& s,int x,int y,int x2,int y2,int g,int h){
    int num = s.puzzle[x2][y2];
    State state = s;
    state.puzzle[x2][y2] = 0;
    state.puzzle[x][y] = num;
    state._g = g;
    state._h = h;
    return state;
}

void Expand(State &current,vector<vector<int>> goal,vector<State> &openStates,vector<State> &closeStates){
    int x = current.get_blank_position()[0];
    int y = current.get_blank_position()[1];
    int width = current._width;
    int g = current._g;

    for(int i = 0;i < 4;i++){
        int x2 = x + delta[i][0];
        int y2 = y + delta[i][1];
        if(CheckVaildMove(x2,y2,width)){
            int g2 = g+1;
            int h2 = Misplaced_Tile_Heuristic(current.puzzle,goal);
            State s = child_state(current,x,y,x2,y2,g2,h2);
            if(!CheckCloseStates(closeStates,s)){
                openStates.emplace_back(s);
                closeStates.emplace_back(s);
            }
        }
    }
}

bool Graph_Search(Problem p,vector<State> closeStates){
    vector<State> openStates;
    State s(p.get_initial_state(),p.get_width(),0);
    openStates.emplace_back(s);
    closeStates.emplace_back(s);

    while(openStates.size() > 0){
        cout << openStates.size() << endl;
        Sort(&openStates);
        State current(openStates.back());
        openStates.pop_back();
        // check if we reach the goal state
        if(current.puzzle == p.get_goal_state()){
            return true;
        }
        Expand(current,p.get_goal_state(),openStates,closeStates);
    }
    return false;
}

int main()
{
    int size;
    int type_of_puzzle;
    cout << "Enter the type of puzzle you want to solve(Ex: 8,15,25,etc): ";
    cin >> type_of_puzzle;
    size = type_of_puzzle+1;
    int width = sqrt(size);
    vector<vector<int>> goal_state = {{1,2,3},{4,5,6},{7,8,0}};
    cout << "Welcome to (862259779) " + to_string(type_of_puzzle) + " puzzle solver.\n";
    Problem problem(width);
    int choice;
    vector<int> puzzle;
    do{
        cout << "Type '1' to use a default puzzle, or '2' to enter your own puzzle.\n";
        cin >> choice;
        if(choice == 1){            // choice 1: use defalut puzzle
            problem.default_Puzzle();
        }
        if(choice == 2){            // choice 2: enter your own puzzle
            cout << "Enter your puzzle, use a zero to represent the blank\n";
            int input;
            vector<int> inputs;
            for(int i = 0;i < width;i++){
                cout << "Enter row " << to_string(i+1) << ", use space or tabs between numbers\n";
                for(int j = 0;j < width;j++){
                    cin >> input;
                    inputs.emplace_back(input);
                }
            }
            problem.insert(inputs);
            problem.set_goal_state(goal_state);
        }
    }while(choice != 1 && choice != 2);
    problem.print_Puzzle();

    // choose which algorithm to use
    int choice2;
    vector<State> closeStates;
    do{
        choices_of_algorithm();
        cin >> choice2;
        if(choice2 == 1){
            if(Graph_Search(problem,closeStates)){
                cout << "Goal!\n";
            }
            else{
                cout << "No!\n";
            }
        }
    }while(choice2 != 1 && choice2 != 2 && choice2 != 3);

    return 0;
}
