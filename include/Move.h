#ifndef MOVE_H
#define MOVE_H
#include <iostream>
#include <vector>
using namespace std;

struct Move {
    int x;
    int y;
    char moveVal;
    Move() {};
    Move(int a, int b) : x(a), y(b) {};
    Move(int a, int b, char c) : x(a), y(b), moveVal(c) {};
    vector<Move> tilesToFlip;// tiles to flip vector 
};
#endif