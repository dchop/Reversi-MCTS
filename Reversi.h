#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Move {
    int x;
    int y;
    Move(int a, int b) : x(a), y(b) {};
};

class Reversi {

    public: 

        void printBoard(vector<vector<char> > const &board); // Prints the board

        void makeMove(vector<vector<char> > &board);

        void checkWin(vector<vector<char> > const &board);

        void flipPieces(vector<vector<char> > &board);

        // Return a list of moves [x,y]
        vector<Move> listMoves(vector<vector<char> > const &board, char currentPlayer, char opponent);

    private:
    
        // Check if the move is in bounds of the 8x8 board
        bool inBound(int x, int y);

        // Check if the current tile has any moves in the specified direction
        Move validMoveDirection(vector<vector<char> > const &board, int x, int y, int dx, int dy, char opponent);

        // Check if the move is already in the list of moves
        bool findMove(vector<Move> const &moves, Move const &targetMove);

};