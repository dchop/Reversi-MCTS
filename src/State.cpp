#include <iostream>
#include <string>
#include <vector>
#include "State.h"

using namespace std;

State::State() {

    for (int i = 0; i < 8; ++i){
        board.push_back(vector<char>(8));
    }

    // Initialize the board with '-'
    for (int i = 0; i < 8; ++i) {
        for(int j = 0; j < 8; ++j) {
            board[i][j] = '-';
        } 
    }
    board[3][3] = 'T';
    board[3][4] = 'F';
    board[4][3] = 'F';
    board[4][4] = 'T';
    
    nextPlayer = 'T';
}

// To be used during the expansion phase and when finding the best move using heuristics
State::State(const State *s2) {
    this->nextPlayer = s2->nextPlayer;
    this->board = s2->board;
}

vector<vector<char> > State::getState() {
    return this->board;
}

char State::getPlayer() {
    return this->nextPlayer;
}

// Toggle to the player who will make the next move on the board
void State::togglePlayer() {
    char currentPlayer = this->nextPlayer;
    this->nextPlayer = (currentPlayer == 'T') ? 'F' : 'T';
}

void State::setMove(Move &pMove, char val) {
    this->board[pMove.x][pMove.y] = val;
}