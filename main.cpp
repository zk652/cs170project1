#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

void default_puzzle(vector<int> &puzzle){
    puzzle.emplace_back(1);
    puzzle.emplace_back(2);
    puzzle.emplace_back(3);
    puzzle.emplace_back(4);
    puzzle.emplace_back(8);
    puzzle.emplace_back(0);
    puzzle.emplace_back(7);
    puzzle.emplace_back(6);
    puzzle.emplace_back(5);
}

void choices_of_algorithm(){
    cout << "Enter your choice of algorithm\n";
    cout << "1. Uniform Cost Search.\n";
    cout << "2. A* with the Misplaced Tile heuristic.\n";
    cout << "3. A* with the Euclidean distance heruistic.\n";
}

void print_Puzzle(const vector<int> &puzzle,int width){
    for(size_t i = 0;i < puzzle.size();i++){
        cout << puzzle[i] << " ";
        if((i+1)%width == 0){
            cout << "\n";
        }
    }
}
int main()
{
    int size;
    int type_of_puzzle;
    cout << "Enter the type of puzzle you want to solve(Ex: 8,15,25,etc): ";
    cin >> type_of_puzzle;
    size = type_of_puzzle+1;
    int width = sqrt(size);
    cout << "Welcome to (862259779)" + to_string(type_of_puzzle) + " puzzle solver.\n";
    int choice;
    vector<int> puzzle;
    do{
        cout << "Type '1' to use a default puzzle, or '2' to enter your own puzzle.\n";
        cin >> choice;
        if(choice == 1){            // choice 1: use defalut puzzle
            default_puzzle(puzzle);
        }
        if(choice == 2){            // choice 2: enter your own puzzle
            cout << "Enter your puzzle, use a zero to represent the blank\n";
            int input;
            for(int i = 0;i < width;i++){
                cout << "Enter row " << to_string(i+1) << ", use space or tabs between numbers\n";
                for(int j = 0;j < width;j++){
                    cin >> input;
                    puzzle.emplace_back(input);
                }
            }
        }
    }while(choice != 1 && choice != 2);
    print_Puzzle(puzzle,width);

    // choose which algorithm to use
    int choice2;
    do{
        choices_of_algorithm();
        cin >> choice2;
    }while(choice2 != 1 && choice2 != 2 && choice2 != 3);

    return 0;
}
