#include <iostream>
#include <string>
#include <vector>
#include "State.h"
#define EMPTY '-'

using namespace std;

const int boardSize = 8;
const int moveDirections[8][2] = {
    {0, 1}, {0, -1}, // South, North
    {1, 0}, {-1, 0}, // East, West
    {1, 1}, {-1, -1}, // SE, NW
    {1, -1}, {-1, 1}, // SW, NE
};

// Check if the move is in bounds of the 8x8 board
bool State::inBound(int x, int y) {
    return (x >= 0 && x < 8 && y >= 0 && y < 8 ) ? true : false;
}

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

    // Black moves first
    nextPlayer = 'F';
}

// Return a list of moves [x,y]
vector<Move> State::listMoves(char currentPlayer, char opponent) {

    vector<Move> possibleMoves;
    int x, y;
    int dx, dy;

    // Check every spot on the board
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {

            // Check if spot is the current player's piece
            if (this->board[i][j] == currentPlayer) {

                // Check in every direction
                for (auto &direction: moveDirections) {

                    dx = direction[0];
                    dy = direction[1];
                    x = i + dx;
                    y = j + dy;

                    // Check if moving in direction goes off the board
                    if (!inBound(x,y))
                        continue;

                    Move newMove = this->validMoveDirection(x, y, dx, dy, opponent);
                    if (newMove.x != -1 && !findMove(possibleMoves, newMove))
                        possibleMoves.push_back(newMove);
                }
            }
        }
    }
    return possibleMoves;
};

// Check if the current tile has any moves in the specified direction
Move State::validMoveDirection(int x, int y, int dx, int dy, char opponent) {

    if (this->board[x][y] == opponent) {

        // Keep moving in direction until the piece is not the opponents piece
        while (this->board[x][y] == opponent) {
            if (inBound(x,y)) {
                x += dx;
                y += dy;
            }
            else {
                break;
            }
        }

        // Check if there is an empty spot
        if (this->board[x][y] == EMPTY)
            return Move(x,y);
    }
    return Move(-1,-1);
}

// Check if the move is already in the list of moves
bool State::findMove(vector<Move> moves, Move targetMove) {

    for (auto &move: moves) {

        if (move.x == targetMove.x && move.y == targetMove.y)
            return true;
    }

    return false;

}
