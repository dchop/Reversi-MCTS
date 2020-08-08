#ifndef REVERSI_H
#define REVERSI_H
#include <iostream>
#include <string>
#include <vector>
#include "State.h"

using namespace std;

class Reversi {

    public: 

        void printBoard(vector<vector<char> > const &board); // Prints the board

        bool checkWin(vector<vector<char> > const &board, int const &numMoves, int const &numOppMoves);

        int reward(vector<vector<char>> const &board, char const &player);

        void makeMove(State *state, Move &newMove);

        void flipPieces(State *state, Move &newMove);

        // Return a list of moves [x,y]
        vector<Move> listMoves(vector<vector<char> > const &board, char currentPlayer, char opponent);

        // Check if the move is already in the list of moves
        Move findMove(vector<Move> const &moves, Move const &targetMove);

    private:
    
        // Check if the move is in bounds of the 8x8 board
        bool inBound(int x, int y);

        // Check if the current tile has any moves in the specified direction
        Move validMoveDirection(vector<vector<char> > const &board, int x, int y, int dx, int dy,
            char currentPlayer, char opponent);

        bool boardFull(vector<vector<char>> const &board);

        char winningPlayer(vector<vector<char> > const &board);
};
#endif