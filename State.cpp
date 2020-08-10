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
    board[4][3] = 'F';
    board[4][4] = 'T';
    
    nextPlayer = 'T';
    this->numIterations = 0;
}

State::State(const State *s2) {

    this->nextPlayer = s2->nextPlayer;
    this->board = s2->board;
    this->numIterations = s2->numIterations;
}

vector<vector<char> > State::getState() {
    return this->board;
}

char State::getPlayer() {
    return this->nextPlayer;
}

int State::getIterations() {
    return this->numIterations;
}

void State::togglePlayer() {
    char currentPlayer = this->nextPlayer;
    this->nextPlayer = (currentPlayer == 'T') ? 'F' : 'T';
}

void State::addIterations(int iterations) {
    this->numIterations += iterations;
}

void State::setMove(Move &pMove, char val) {
    this->board[pMove.x][pMove.y] = val;
}