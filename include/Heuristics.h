#ifndef HEURISTICS_H
#define HEURISTICS_H
#include <vector>
#include "Move.h"
#include "Reversi.h"
using namespace std;

int coinParity(vector<vector<char> > const &board);

int mobilityHeuristic(vector<vector<char> > const &board);

int checkCorners(vector<vector<char> > const &board, char player);

int cornerHeuristic(vector<vector<char> > const &board);

Move findBestMove(Reversi game, State *state, vector<Move> &moves);

#endif