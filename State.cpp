#include <iostream>
#include <string>
#include <vector>
#include "State.h"

using namespace std;

State::State() {

    for (int i = 0; i < 8; ++i){
        board.push_back(vector<char>(8));
    }
    for (int i = 0; i < 8; ++i) { // initialize the board with '-'
        for(int j = 0; j < 8; ++j) {
            board[i][j] = '-';
        } 
    }
    board[3][3] = 'T';
    board[3][4] = 'F';
    board[3][5] = 'T';
    board[4][4] = 'F';
    board[4][5] = 'F';
    board[5][5] = 'F';
    board[6][5] = 'F';
    

    // Black moves first
    nextPlayer = 'F';
}

vector<vector<char> > State::getState() {
    return this->board;
}