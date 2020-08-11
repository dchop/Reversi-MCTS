#include <iostream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <chrono>
#include "Mcts.h"
#include "Heuristics.h"

// Used to balance exploitation and exploration between the MCTS tree
double uct(Node *root) {

    double visits = root->visits;
    double pVisits = root->parent->visits;
    double reward = root->reward;
    double c = sqrt(2);

    if (visits == 0)
        return INFINITY;

    return reward / visits + c * sqrt(log(pVisits) / visits);
}

// Find the best leaf node
Node* select(Node *root) {

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

// Expand all possible states from root
Node* expand(Node *root, Reversi game) {

    char currentPlayer = root->state->getPlayer();
    char opponent = currentPlayer == 'T' ? 'F' : 'T';
    vector<Move> playerMoves = game.listMoves(root->state->getState(), currentPlayer, opponent);
    vector<Move> oppMoves = game.listMoves(root->state->getState(), opponent, currentPlayer);
    int randomVal = 0;

    // Check if the game is finished
    if (!game.checkWin(root->state->getState(), playerMoves.size(), oppMoves.size()) && root->children.size() == 0) {
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

// Simulate the current state of the game until a win, loss or draw
int simulate(Node *root, Reversi game) {

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

        // Toggle to the other perspective of the game
        currentPlayer = currentPlayer == 'T' ? 'F' : 'T';
        opponent = currentPlayer == 'T' ? 'F' : 'T';

        // Check if the game is done
        moves1 = game.listMoves(root->state->getState(), currentPlayer, opponent);
        moves2 = game.listMoves(root->state->getState(), opponent, currentPlayer);
        if (game.checkWin(root->state->getState(), moves1.size(), moves2.size())) {
            break;
        }
    }

    // Return reward value from the perspective of the state's next turn
    reward = game.reward(root->state->getState(), root->state->getPlayer());
    winner = game.winningPlayer(root->state->getState());
    return (winner == root->state->getPlayer()) ? reward : -reward;
}

// Simulate the current state of the game until a win, loss or draw
int improvedSimulate(Node *root, Reversi game) {

    char currentPlayer = root->state->getPlayer();
    char opponent = currentPlayer == 'T' ? 'F' : 'T';
    vector<vector<char>> tempState = root->state->getState();
    vector<Move> moves1 = game.listMoves(root->state->getState(), currentPlayer, opponent);
    vector<Move> moves2 = game.listMoves(root->state->getState(), opponent, currentPlayer);
    int reward = 0;
    Move move1;
    Move move2;
    char winner;

    while (true) {

        if (moves1.size() > 0) {
            move1 = findBestMove(game, root->state, moves1);
            game.makeMove(root->state, move1);
        }

        // Toggle to the other perspective of the game
        currentPlayer = currentPlayer == 'T' ? 'F' : 'T';
        opponent = currentPlayer == 'T' ? 'F' : 'T';

        // Check if the game is done
        moves1 = game.listMoves(root->state->getState(), currentPlayer, opponent);
        moves2 = game.listMoves(root->state->getState(), opponent, currentPlayer);
        if (game.checkWin(root->state->getState(), moves1.size(), moves2.size())) {
            break;
        }
    }

    // Return reward value from the perspective of the state's next turn
    reward = game.reward(root->state->getState(), root->state->getPlayer());
    winner = game.winningPlayer(root->state->getState());
    return (winner == root->state->getPlayer()) ? reward : -reward;
}

// Update all values from root to node
void backprop(Node *root, double result) {

    Node *temp = root;

    while (temp != NULL) {
        temp->visits += 1;
        temp->reward += result;

        // Includes perspective view of node at each level of the tree
        result = -result;
        temp = temp->parent;
    }
}

// Returns the node with the highest number of visits
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

// Returns the node with the highest reward value
Node* bestChildWins(Node *root) {

    Node *maxNode = NULL;
    double val = 0;
    double max = -INFINITY;

    for (auto &child: root->children) {
        
        val = child->reward;
        if (val > max) {
            maxNode = child;
            max = val;
        }
    }
    return maxNode;
}

// Base MCTS algorithm with UCT and random playouts
Move basicMCTS(Node *root, Reversi game, Player &player, int duration) {
    Node *leaf = NULL;
    Node *child = NULL;
    int result = 0;
    int numIterations = 0;
    auto tStart = chrono::high_resolution_clock::now();
    chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();

    while (chrono::high_resolution_clock::now() - start < chrono::seconds(duration)) {
        leaf = select(root);
        child = expand(leaf, game);
        result = simulate(child, game);
        backprop(child, result);
        numIterations += 1;
    }

    // Count the number of iterations ran
    player.iterations += numIterations;

    // Add up the time spent searching moves
    auto tEnd = chrono::high_resolution_clock::now();
    double totalTime = chrono::duration_cast<chrono::duration<double>>(tEnd - tStart).count();
    player.searchTime += totalTime;

    return bestChildWins(root)->action;
}

// MCTS algorithm with UCT and heuristic driven playouts
Move improvedMCTS(Node *root, Reversi game, Player &player, int duration) {
    Node *leaf = NULL;
    Node *child = NULL;
    int result = 0;
    int numIterations = 0;
    auto tStart = chrono::high_resolution_clock::now();
    chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();

    while (chrono::high_resolution_clock::now() - start < chrono::seconds(duration)) {
        leaf = select(root);
        child = expand(leaf, game);
        result = improvedSimulate(child, game);
        backprop(child, result);
        numIterations += 1;
    }

    // Count the number of iterations ran
    player.iterations += numIterations;

    // Add up the time spent searching moves
    auto tEnd = chrono::high_resolution_clock::now();
    double totalTime = chrono::duration_cast<chrono::duration<double>>(tEnd - tStart).count();
    player.searchTime += totalTime;

    return bestChild(root)->action;
}