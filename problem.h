#ifndef PROBLEM_H
#define PROBLEM_H
#include <iostream>
#include <vector>

class Problem
{
public:
    Problem(int width = 0):_width(width){}      //constr
    void insert(std::vector<int> v);         // insert element to the puzzle
    void print_Puzzle();            // prints the puzzle
    //void default_Puzzle();          // generates a default puzzle
    void set_default_Puzzle();
    void set_goal_state(std::vector<std::vector<int>> v){goal_state = v;}
    std::vector<std::vector<int>> get_initial_state(){return initial_state;}
    std::vector<std::vector<int>> get_goal_state(){return goal_state;}
    int get_width(){return _width;}
private:
    std::vector<std::vector<int>> initial_state;
    int _width;   // width of the puzzle
    std::vector<std::vector<int>> goal_state;
    int operators[4] = {-_width,_width,-1,1};    // up, down, left, right

};

#endif // PROBLEM_H
