#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <stdlib.h>
#include "Reversi.h"
#define EMPTY '-'
using namespace std;

const int boardSize = 8;
const int moveDirections[8][2] = {
    {0, 1}, {0, -1}, // South, North
    {1, 0}, {-1, 0}, // East, West
    {1, 1}, {-1, -1}, // SE, NW
    {1, -1}, {-1, 1}, // SW, NE
};


// Prints the board
void Reversi::printBoard(vector<vector<char> > const &board) {
    cout << endl << "  +---+---+---+---+---+---+---+---+ "<< endl;
    for (int i = 0; i < 8; i++){
        cout << i << " |";
        for (int j = 0; j < 8; j++)
        {
            cout << " " << board[i][j] << " |";
        }
        cout << endl << "  +---+---+---+---+---+---+---+---+ "<< endl;
    }
    cout << "    0   1   2   3   4   5   6   7 " << endl;
}

// Check if the game is over
bool Reversi::checkWin(vector<vector<char> > const &board, int const &numMoves, int const &numOppMoves) {

    // Either the board is full or there is no move to be made
    if (this->boardFull(board))
        return true;
    else if (numMoves == 0 && numOppMoves == 0)
        return true;
    else
        return false;
}

// Return the score of the game
tuple<int, int> Reversi::score(vector<vector<char>> const &board) {
    int black = 0;
    int white = 0;
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            if (board[i][j] == 'T')
                white += 1;
            else if (board[i][j] == 'F')
                black += 1;
        }
    }

    return make_tuple(white, black);
}

// Return the winner of the game or if a draw has occurred
char Reversi::winningPlayer(vector<vector<char>> const &board) {
    int white, black;
    tie(white, black) = this->score(board);

    if (white > black)
        return 'T';
    else if (white < black)
        return 'F';
    else
        return 'D';
}

// Determine if someone has won the game or not
int Reversi::reward(vector<vector<char>> const &board, char const &player) {
    char winner = this->winningPlayer(board);
    char opponent = player == 'T' ? 'F' : 'T';

    if (winner == player || winner == opponent) 
        return 1;
    else // Game resulted in draw
        return 0;
}

// Return if the board is completely filled
bool Reversi::boardFull(vector<vector<char>> const &board) {

    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            if (board[i][j] == '-')
                return false;
        }
    }
    return true;
}

// Make a move on the board state
void Reversi::makeMove(State *state, Move &newMove) {
    state->setMove(newMove, newMove.moveVal);
    this->flipPieces(state, newMove);
}

// Flip the pieces once a move has been performed
void Reversi::flipPieces(State *state, Move &newMove) {
    for (auto &tile:newMove.tilesToFlip)
        state->setMove(tile, newMove.moveVal);
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

                    Move newMove = this->validMoveDirection(board, x, y, dx, dy, currentPlayer, opponent);
                    Move returnFromFindMove = findMove(possibleMoves, newMove);

                    // If the move is already in the possible moves
                    if (newMove.x != -1 &&  returnFromFindMove.x != -1){
                        x = newMove.x;
                        y = newMove.y;

                        // Find which tiles to flip if the move were to be made
                        while (1){
                            x -= direction[0];
                            y -= direction[1];
                            if (x == i && y == j){
                                break;
                            }
                            Move tempMove = {x, y};

                            for(std::vector<Move>::size_type i = 0; i != possibleMoves.size(); i++) {
                                // Check if move has tiles to flip in multiple directions
                                if(possibleMoves[i].x == returnFromFindMove.x && possibleMoves[i].y == returnFromFindMove.y){
                                    possibleMoves[i].tilesToFlip.push_back(tempMove);
                                    break;
                                }
                            }
                        }
                    }
                    // New possible move
                    if (newMove.x != -1 && returnFromFindMove.x == -1){
                        x = newMove.x;
                        y = newMove.y;

                        // Find which tiles to flip if the move were to be made
                        while (1){
                            x -= direction[0];
                            y -= direction[1];
                            if (x == i && y == j){
                                break;
                            }
                            Move tempMove = {x, y};
                            newMove.tilesToFlip.push_back(tempMove); 
                        }
                        possibleMoves.push_back(newMove);
                    }
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
    char currentPlayer, char opponent) {

    if (board[x][y] == opponent) {

        // Keep moving in direction until the piece is not the opponents piece
        while (board[x][y] == opponent) {
            x += dx;
            y += dy;
            if (!inBound(x,y)) {
                x -= dx;
                y -= dy;
                break;
            }
        }

        // Check if there is an empty spot
        if (board[x][y] == EMPTY) {
            return Move(x, y, currentPlayer);
        }
    }
    return Move(-1,-1);
}

// Check if the move is already in the list of moves
Move Reversi::findMove(vector<Move> const &moves, Move const &targetMove) {

    for (auto &move: moves) {

        if (move.x == targetMove.x && move.y == targetMove.y)
            return move;
    }
    // return the index where the move is
    return Move(-1, -1);
}