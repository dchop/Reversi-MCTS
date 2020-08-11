#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include "Reversi.h"
using namespace std;

class Player {

    public: 
        Player(char player, int moveType);
        Player();
        char player;
        string playerType;
        int moveType;
        int iterations;
        double searchTime;
        Move getMove(Reversi game, State *state, vector<Move> const &moves);
};


#endif