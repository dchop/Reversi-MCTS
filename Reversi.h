#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Reversi {

    public: 
        Reversi(); // Constructor that sets up a new board

        void printBoard(); // Prints the board

        void makeMove();

        void checkWin();

        void flipPieces();

    private:
        vector<vector<char> > board; 

};