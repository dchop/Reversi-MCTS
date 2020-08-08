#ifndef STATE_H
#define STATE_H
#include <iostream>
#include <string>
#include <vector>
#include "Move.h"

using namespace std;

class State {
    public:

        State();
        
        State(const State *s2);

        vector<vector<char> > getState();

        char getPlayer();

        void setMove(Move &playerMove, char val);

    private:
        // Indicates who makes the next move for the current board state
        char nextPlayer;

        // Holds the board state
        vector<vector<char> > board;
};
#endif