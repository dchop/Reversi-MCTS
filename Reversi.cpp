#include <iostream>
#include <string>
#include <vector>
#include "Reversi.h"
#define EMPTY '-'

const int boardSize = 8;
const int moveDirections[8][2] = {
    {0, 1}, {0, -1}, // South, North
    {1, 0}, {-1, 0}, // East, West
    {1, 1}, {-1, -1}, // SE, NW
    {1, -1}, {-1, 1}, // SW, NE
};

using namespace std;

// Prints the board
void Reversi::printBoard(vector<vector<char> > const &board) {
    cout << endl << "  +---+---+---+---+---+---+---+---+ "<< endl;
    for (int i = 0; i < 8; i++){
        cout << i << " |";
        for (int j = 0; j < 8; j++)
        {
            cout << " " << board[j][i] << " |";
        }
        cout << endl << "  +---+---+---+---+---+---+---+---+ "<< endl;
    }
    cout << "    0   1   2   3   4   5   6   7 " << endl;
}

void Reversi::makeMove(vector<vector<char> > &board) {


}

void Reversi::checkWin(vector<vector<char> > const &board) {
    int boardFull;

    for (int i = 0; i < 8; i++){ // Needs more checks
        for (int j = 0; j < 8; j++){
            if (board[i][j] == '-'){
                boardFull = 0;
                break;
            }
            boardFull = 1;
        }
    }

}

void Reversi::flipPieces(vector<vector<char> > &board) {


}

// Return a list of moves [x,y]
vector<Move> Reversi::listMoves(vector<vector<char> > const &board, char currentPlayer, char opponent) {

    vector<Move> possibleMoves;
    int x, y;
    int dx, dy;

    // Check every spot on the board
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {

            // Check if spot is the current player's piece
            if (board[i][j] == currentPlayer) {

                // Check in every direction
                for (auto &direction: moveDirections) {

                    dx = direction[0];
                    dy = direction[1];
                    x = i + dx;
                    y = j + dy;

                    // Check if moving in direction goes off the board
                    if (!inBound(x,y))
                        continue;

                    Move newMove = this->validMoveDirection(board, x, y, dx, dy, opponent);
                    if (newMove.x != -1 && !findMove(possibleMoves, newMove))
                        possibleMoves.push_back(newMove);
                }
            }
        }
    }
    return possibleMoves;
};

// Check if the move is in bounds of the 8x8 board
bool Reversi::inBound(int x, int y) {
    return (x >= 0 && x < 8 && y >= 0 && y < 8 ) ? true : false;
}

// Check if the current tile has any moves in the specified direction
Move Reversi::validMoveDirection(vector<vector<char> > const &board, int x, int y, int dx, int dy, 
    char opponent) {

    if (board[x][y] == opponent) {

        // Keep moving in direction until the piece is not the opponents piece
        while (board[x][y] == opponent) {
            if (inBound(x,y)) {
                x += dx;
                y += dy;
            }
            else {
                break;
            }
        }

        // Check if there is an empty spot
        if (board[x][y] == EMPTY)
            return Move(x,y);
    }
    return Move(-1,-1);
}

// Check if the move is already in the list of moves
bool Reversi::findMove(vector<Move> const &moves, Move const &targetMove) {

    for (auto &move: moves) {

        if (move.x == targetMove.x && move.y == targetMove.y)
            return true;
    }

    return false;
}