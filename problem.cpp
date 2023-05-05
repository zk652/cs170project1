#include "problem.h"

void Problem::insert(std::vector<int> v){
    std::vector<int> vec;
    for(int i = 0;i < v.size();i++){
        vec.emplace_back(v[i]);
        if((i+1)%_width == 0){
            initial_state.emplace_back(vec);
            vec.clear();
        }
    }
}

void Problem::print_Puzzle(){
//    for(size_t i = 0;i < initial_state.size();i++){
//        std::cout << initial_state[i] << " ";
//        if((i+1)%_width == 0){
//            std::cout << "\n";
//        }
//    }
    for(int i = 0;i < _width;i++){
        for(int j = 0;j < _width;j++){
            std::cout << initial_state[i][j] << " ";
        }
        std::cout << "\n";
    }
}

void Problem::default_Puzzle(){
    initial_state[0].emplace_back(1);
    initial_state[0].emplace_back(2);
    initial_state[0].emplace_back(3);
    initial_state[1].emplace_back(4);
    initial_state[1].emplace_back(8);
    initial_state[1].emplace_back(0);
    initial_state[2].emplace_back(7);
    initial_state[2].emplace_back(6);
    initial_state[2].emplace_back(5);
}
