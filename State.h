#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Move {
    int x;
    int y;
    Move(int a, int b) : x(a), y(b) {};
};

class State {
    public:

        State();

        // Return a list of moves [x,y]
        vector<Move> listMoves(char currentPlayer, char opponent);

    private:
        // Indicates who makes the next move for the current board state
        char nextPlayer;

        // Holds the board state
        vector<vector<char> > board;

        // Check if the move is in bounds of the 8x8 board
        bool inBound(int x, int y);

        // Check if the current tile has any moves in the specified direction
        Move validMoveDirection(int x, int y, int dx, int dy, char opponent);

        // Check if the move is already in the list of moves
        bool findMove(vector<Move> moves, Move targetMove);
};