#include <iostream>
#include <string>
#include <vector>

using namespace std;

class State {
    public:

        State();

        vector<vector<char> > getState();

    private:
        // Indicates who makes the next move for the current board state
        char nextPlayer;

        // Holds the board state
        vector<vector<char> > board;
};