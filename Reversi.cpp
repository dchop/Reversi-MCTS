#include <iostream>
#include <string>
#include <vector>
#include "Reversi.h"
#include "State.h"
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

vector<vector <char>> Reversi::makeMove(vector<vector<char> > const &board, Move newMove) {
    State tempBoard;
    vector<vector<char> > temp = tempBoard.getState();
    temp = board;
    temp[newMove.x][newMove.y] = 'T';
    // std::vector<int>::iterator it;
    // it = board.insert(newMove.x, newMove.y, 'T');
    // board[newMove.x][newMove.y] = 'T';
    vector<vector<char>> boardWithFlippedTiles = flipPieces(temp, newMove);
    return boardWithFlippedTiles;
    // call tilesToFlipFunction 

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

vector<vector<char>> Reversi::flipPieces(vector<vector<char> > &board, Move newMove) {
    for(std::vector<Move>::size_type i = 0; i != newMove.tilesToFlip.size(); i++) {
     board[newMove.tilesToFlip[i].x][newMove.tilesToFlip[i].y] = 'T';
    }   
return board;
}

// Return a list of moves [x,y]
vector<Move> Reversi::listMoves(vector<vector<char> > const &board, char currentPlayer, char opponent) {

    vector<Move> possibleMoves;
    vector<Move> flipTiles;
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
                    Move returnFromFindMove = findMove(possibleMoves, newMove);
                    if (newMove.x != -1 &&  returnFromFindMove.x != -1){
                        x = newMove.x;
                        y = newMove.y;
                        while (1){
                            x -= direction[0];
                            y -= direction[1];
                            if (x == i && y == j){
                                break;
                            }
                            Move tempMove = {x, y};
                            // flipTiles.push_back(tempMove);
                            for(std::vector<Move>::size_type i = 0; i != possibleMoves.size(); i++) {
                                if(possibleMoves[i].x == returnFromFindMove.x && possibleMoves[i].y){
                                    possibleMoves[i].tilesToFlip.push_back(tempMove);
                                    break;
                                }
                                // printf("moves are: %d %d", newMove.tilesToFlip[i].x, newMove.tilesToFlip[i].x);
                            }
                            // newMove.tilesToFlip.push_back(tempMove);
                            // possibleMoves.push_back(newMove);
                        }
                    }
                    if (newMove.x != -1 && returnFromFindMove.x == -1){
                        // if (move in possibleMoves){
                        //     append the flipped pieces (coordinates) of this current move to the one thats already in the possibleMoves of its flipped pieces vector of the struct
                        // }
                        // check i
                        
                    // If its already in the possible moves then it affects tiles in more than one
                    // direction
                        x = newMove.x;
                        y = newMove.y;
                        while (1){
                            x -= direction[0];
                            y -= direction[1];
                            if (x == i && y == j){
                                break;
                            }
                            Move tempMove = {x, y};
                            flipTiles.push_back(tempMove);
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
Move Reversi::findMove(vector<Move> const &moves, Move const &targetMove) {

    for (auto &move: moves) {

        if (move.x == targetMove.x && move.y == targetMove.y)
            return Move(move.x, move.y);
    }
    // return the index where the move is
    return Move(-1, -1);
}