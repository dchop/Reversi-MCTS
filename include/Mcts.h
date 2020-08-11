#ifndef MCTS_H
#define MCTS_H
#include "Node.h"
#include "Reversi.h"
#include "Player.h"

double uct(Node *root);

Node* select(Node *root);

Node* improvedSelect(Node *root);

Node* expand(Node *root, Reversi game);

int simulate(Node *root, Reversi game);

int improvedSimulate(Node *root, Reversi game);

void backprop(Node *root, double result);

void improvedBackprop(Node *root, double result);

Node* bestChild(Node *root);

Move basicMCTS(Node *root, Reversi game, Player &player, int duration=5);

Move improvedMCTS(Node *root, Reversi game, Player &player, int duration=5);

#endif