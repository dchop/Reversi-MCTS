#include <iostream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <chrono>
#include "Node.h"
#include "Reversi.h"

double uct(Node *root) {

    double visits = root->visits;
    double pVisits = root->parent->visits;
    double reward = root->reward;
    double c = sqrt(2);

    if (visits == 0)
        return INFINITY;

    return reward / visits + c * sqrt(log(pVisits) / visits);
}

Node* selection(Node *root) {
    // Find the best leaf node

    Node *temp = root;
    double val = 0;
    double max;

    // Traverse down the tree by taking the path with the largest UCT value at level
    while (temp->children.size() > 0) {

        max = -INFINITY;
        for (auto &child: temp->children) {

            val = uct(child);
            if (val > max) {
                temp = child;
                max = val;
            }
        }
    }
    return temp;
}

Node* expand(Node *root, Reversi game) {
    // Expand all possible states from root

    char currentPlayer = root->state->getPlayer();
    char opponent = currentPlayer == 'T' ? 'F' : 'T';
    vector<Move> playerMoves = game.listMoves(root->state->getState(), currentPlayer, opponent);
    vector<Move> oppMoves = game.listMoves(root->state->getState(), opponent, currentPlayer);
    int randomVal = 0;

    // Check if the game is finished
    if (!game.checkWin(root->state->getState(), playerMoves.size(), oppMoves.size())) {
        if (playerMoves.size() > 0) {
            for (auto &move: playerMoves) {

                // Copy state and apply move
                State *baseState = new State(root->state);
                Node *newNode = new Node(baseState, root, move);
                game.makeMove(newNode->state, move);
                root->children.push_back(newNode);
            }
            randomVal = rand() % root->children.size();

            return root->children[randomVal];
        }
    }
    return root;
}

int simulate(Node *root, Reversi game) {
    // Simulate the current state of the game until a win, loss or draw

    char currentPlayer = root->state->getPlayer();
    char opponent = currentPlayer == 'T' ? 'F' : 'T';
    vector<vector<char>> tempState = root->state->getState();
    vector<Move> moves1 = game.listMoves(root->state->getState(), currentPlayer, opponent);
    vector<Move> moves2 = game.listMoves(root->state->getState(), opponent, currentPlayer);
    int randVal = 0;
    int reward = 0;
    char winner;

    while (true) {

        if (moves1.size() > 0) {
            // Randomly select move from avaliable moves
            randVal = rand() % moves1.size();

            // Make the move on the state
            game.makeMove(root->state, moves1[randVal]);
        }

        // Check if the game is done
        moves1 = game.listMoves(root->state->getState(), currentPlayer, opponent);
        moves2 = game.listMoves(root->state->getState(), opponent, currentPlayer);
        if (game.checkWin(root->state->getState(), moves1.size(), moves2.size())) {
            break;
        }

        // Toggle to the other view of the game
        currentPlayer = currentPlayer == 'T' ? 'F' : 'T';
        opponent = currentPlayer == 'T' ? 'F' : 'T';
    }

    // Return reward value from the perspective of the state's next turn
    reward = game.reward(root->state->getState(), root->state->getPlayer());
    winner = game.winningPlayer(root->state->getState());
    return (winner != root->state->getPlayer()) ? reward : -reward;
}

void backpropgate(Node *root, double result) {
    // Update all values from root to node

    Node *temp = root;

    while (temp != NULL) {
        temp->visits += 1;
        temp->reward += result;

        result = -result;
        temp = temp->parent;
    }
}

Node* bestChild(Node *root) {

    Node *maxNode = NULL;
    double val = 0;
    double max = -INFINITY;

    for (auto &child: root->children) {
        
        val = child->visits;
        if (val > max) {
            maxNode = child;
            max = val;
        }
    }
    return maxNode;
}

Move basicMCTS(Node *root, Reversi game, int duration=5) {
    Node *leaf = NULL;
    Node *child = NULL;
    int result = 0;
    chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();

    // for (int i = 0; i < iterations; i++) {
    while (chrono::high_resolution_clock::now() - start < chrono::seconds(duration)) {
        leaf = selection(root);
        child = expand(leaf, game);
        result = simulate(child, game);
        backpropgate(child, result);
    }

    // printf("MCTS finished!\n");
    return bestChild(root)->action;
}