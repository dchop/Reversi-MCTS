#include <iostream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include "Node.h"

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
    double max = -INFINITY;

    // Traverse down the tree by taking the path with the largest UCT value at level
    while (temp->children.size() > 0) {

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
    vector<Move> moveList = game.listMoves(root->state->getState(), currentPlayer, opponent);
    int randomVal = 0;

    // TODO: Need check is game over method
    // Check if the game is finished
    for (auto &move: moveList) {
        // Copy state and apply move
        // Node *newNode = new Node();
        Node *newNode;
        root->children.push_back(newNode);
    }

    randomVal = rand() % root->children.size();
    return root->children[randomVal];
}

// TODO: Need game functions to simulate game
int simulate(Node *root, Reversi game) {
    // Simulate the current state of the game until a win, loss or draw

    char currentPlayer = root->state->getPlayer();
    vector<vector<char>> tempState = root->state->getState();

    while (true) {

        // Randomly select move from avaliable moves

        // Make the move on the state

        // Toggle the current player
        currentPlayer = currentPlayer == 'T' ? 'F' : 'T';
    }

    // Toggle to the winning player
    char winningPlayer = currentPlayer == 'T' ? 'F' : 'T';

    // TODO: Get reward value from method

    return 0;
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

Move basicMCTS(Node *root, Reversi game, char player, int iterations=1000) {
    Node *leaf = NULL;
    Node *child = NULL;
    int result = 0;

    for (int i = 0; i < iterations; i++) {
        *leaf = selection(root);
        *child = expand(leaf, game);
        result = simulate(child, game);
        backpropgate(child, result);
    }

    return bestChild(root)->action;
}