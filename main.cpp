#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "problem.h"
#include <algorithm>
const int delta[4][2]{{-1,0},{0,-1},{1,0},{0,1}};// up, left,down,right
using namespace std;
struct Tree{

};
struct State{
    State(const State& s){puzzle = s.puzzle;_width = s._width;_g = s._g;_h = s._h;}
    State(vector<vector<int>> p,int width,int g,int h = 0):puzzle(p),_width(width),_g(g),_h(h){}
    vector<vector<int>> puzzle;
    void set_parent(State *parent){
        _parent = parent;
    }
    int _width;
    int _g;
    int _h;
    State* _parent;
    vector<int> get_blank_position(){
        for(int i = 0;i < _width;i++){
            for(int j = 0;j < _width;j++){
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
pair<int,int> get_position(vector<vector<int>> v,int entry){
    for(int i = 0;i < v.size();i++){
        for(int j = 0;j < v.size();j++){
            if(v[i][j] == entry){
                return make_pair(i,j);
            }
        }
    }
    return make_pair(-1,-1);
}
int Manhattan_Heuristic(vector<vector<int>> current,vector<vector<int>> goal,int width){
    int size = width*width-1;
    vector<pair<int,int>> position1;
    vector<pair<int,int>> position2;
    int sum = 0;
//    int sum2 = 0;
    // get the positions for all entries in each puzzle
    for(int i = 1;i <= size;i++){
        position1.emplace_back(get_position(current,i));
        position2.emplace_back(get_position(goal,i));
    }
    for(int i = 0;i < size;i++){
//        sum += sqrt(pow(abs(position1[i].first - position2[i].first),2) +
//                       pow(abs(position1[i].second - position2[i].second),2));
        sum += abs(position1[i].first - position2[i].first) +
                       abs(position1[i].second - position2[i].second);

//        sum2 = round(sum);
    }
    return sum;
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

int Expand(State &current,vector<vector<int>> goal,vector<State> &frontier,vector<State> &closeStates,int choice){
    int x = current.get_blank_position()[0];
    int y = current.get_blank_position()[1];
    int width = current._width;
    int g = current._g;
    int nodes = 0;
    for(int i = 0;i < 4;i++){
        int x2 = x + delta[i][0];
        int y2 = y + delta[i][1];
        if(CheckVaildMove(x2,y2,width)){
            int g2 = g+1;
            int h2 = 0;
            State s = child_state(current,x,y,x2,y2,g2,h2);
            if(choice == 2){
                h2 = Misplaced_Tile_Heuristic(s.puzzle,goal);
            }else if(choice == 3){
                h2 = Manhattan_Heuristic(s.puzzle,goal,width);
            }
            s._h = h2;
            s.set_parent(&current);
            if(!CheckCloseStates(closeStates,s)){
                frontier.emplace_back(s);
                closeStates.emplace_back(s);
                nodes = 1;
            }
        }
    }
    return nodes;
}

bool Graph_Search(Problem p,vector<State> closeStates,int choice){
    vector<State> frontier;
    State s(p.get_initial_state(),p.get_width(),0);
    s.set_parent(nullptr);
    frontier.emplace_back(s);
    closeStates.emplace_back(s);
    int nodes = 0;
    while(frontier.size() > 0){
        Sort(&frontier);
        State current(frontier.back());
        frontier.pop_back();
        cout << "The best state to expand with g(n) = " + to_string(current._g) + " and h(n) = " + to_string(current._h) + " is...\n";
        cout << "Number of expanded nodes: " << to_string(nodes) << endl;
        current.print_Puzzle();
        cout << endl;
        // check if we reach the goal state
        if(current.puzzle == p.get_goal_state()){
            cout << "Number of expanded nodes: " << to_string(nodes) << endl;
            cout << "Number of frontier nodes: " << to_string(frontier.size()) << endl;
            return true;
        }
        nodes += Expand(current,p.get_goal_state(),frontier,closeStates,choice);
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
//    vector<vector<int>> goal_state = {{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,0}};
    cout << "Welcome to (862259779) " + to_string(type_of_puzzle) + " puzzle solver.\n";
    Problem problem(width);
    int choice;
    vector<int> puzzle;
    do{
        cout << "Type '1' to use a default puzzle, or '2' to enter your own puzzle.\n";
        cin >> choice;
        if(choice == 1){            // choice 1: use defalut puzzle
            //problem.default_Puzzle();
            if(choice == 1){            // choice 1: use default puzzle
                problem.set_default_Puzzle();
                problem.set_goal_state(goal_state);
            }
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
        if(Graph_Search(problem,closeStates,choice2)){
            cout << "Goal!\n";
        }
        else{
            cout << "No!\n";
        }
    }while(choice2 != 1 && choice2 != 2 && choice2 != 3);

    return 0;
}
