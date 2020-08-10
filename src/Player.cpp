#include <iostream>
#include <stdlib.h>
#include "Player.h"
#include "Node.h"
#include "Mcts.h"
using namespace std;

Player::Player(){
    this->player = 'T';
    this->numWins = 0;
    this->moveType = 3;
}

Player::Player(char player, int moveType) {
    this->player = player;
    this->numWins = 0;
    this->moveType = moveType;
}

Move Player::getMove(Reversi game, State *state, vector<Move>const &moves) {

    // pureMCTS
    if (this->moveType == 0) {
        Node *root = new Node(state);
        Move bestMove = basicMCTS(root, game);
        delete root;
        return game.findMove(moves, bestMove);
    }
    // improvedMCTS
    else if (this->moveType == 1) {
        Node *root = new Node(state);
        Move bestMove = improvedMCTS(root, game);
        delete root;
        return game.findMove(moves, bestMove);
    }
    // inputPlayer
    else if (this->moveType == 2) {
        int x, y;
        Move result;

        do {
            printf("Enter a X Y coordinate: ");
            cin >> x >> y;
            result = game.findMove(moves, Move(x,y));
            if (result.x == -1)
                printf("The move (%d %d) is not a possible move\n", x, y);

        } while(result.x == -1);

        return result;
    }
    // randomPlayer
    else {
        return moves[rand() % moves.size()];
    }
}