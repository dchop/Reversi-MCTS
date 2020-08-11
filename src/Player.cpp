#include <iostream>
#include <stdlib.h>
#include <chrono>
#include "Player.h"
#include "Mcts.h"
using namespace std;

bool validDigits(char a, char b) {
    return isdigit(a) && isdigit(b);
}

Player::Player(){
    this->player = 'T';
    this->iterations = 0;
    this->searchTime = 0;
    this->moveType = 3;
}

Player::Player(char player, int moveType) {
    this->player = player;
    this->iterations = 0;
    this->searchTime = 0;
    this->moveType = moveType;
}

// Interface function to get a move based on the moveType
Move Player::getMove(Reversi game, State *state, vector<Move>const &moves) {

    // pureMCTS
    if (this->moveType == 0) {
        Node *root = new Node(state);
        Move bestMove = basicMCTS(root, game, *this);
        delete root;
        return game.findMove(moves, bestMove);
    }
    // improvedMCTS
    else if (this->moveType == 1) {
        Node *root = new Node(state);
        Move bestMove = improvedMCTS(root, game, *this);
        delete root;
        return game.findMove(moves, bestMove);
    }
    // inputPlayer
    else if (this->moveType == 2) {
        string input;
        int x, y;
        Move result;

        do {
            printf("Enter a X Y coordinate: ");
            getline(cin, input);


            if (!validDigits(input[0], input[2])) {
                printf("\nInput is invalid! Should be inputted like: 3 2\n");
                continue;
            }

            x = input[0] - 48;
            y = input[2] - 48;

            result = game.findMove(moves, Move(x,y));
            if (result.x == -1) {
                printf("\nThe move (%d %d) is not a possible move\n", x, y);
                continue;
            }
            else
                break;

        } while(!validDigits(input[0], input[1]) || result.x == -1);

        return result;
    }
    // randomPlayer
    else {
        return moves[rand() % moves.size()];
    }
}