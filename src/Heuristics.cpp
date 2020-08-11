#include <vector>
#include "Heuristics.h"
using namespace std;

int coinParity(vector<vector<char> > const &board){
    vector<vector<char> > tempBoard = board;
    int maxT_tiles = 0;
    int maxF_tiles = 0;

    for (int i = 0; i < 8; ++i) {
        for(int j = 0; j < 8; ++j) {
            if(tempBoard[i][j] == 'T'){
                maxT_tiles++;
            }
            else if(tempBoard[i][j] == 'F'){
                maxF_tiles++;
            }
        } 
    }
    int max, min;

    if(maxT_tiles > maxF_tiles){
        max = maxT_tiles;
        min = maxF_tiles;
    }
    else{
        max = maxF_tiles;
        min = maxT_tiles;
    }
    int heuristicValue = 100 * (max - min)/(max + min);
    return heuristicValue;
}

int mobilityHeuristic(vector<vector<char> > const &board){
    vector<vector<char> > tempBoard = board;
    Reversi tempGame;
    int maxT_tiles = 0;
    int maxF_tiles = 0;
    for (int i = 0; i < 8; ++i) {
        for(int j = 0; j < 8; ++j) {
            if(tempBoard[i][j] == 'T'){
                maxT_tiles++;
            }
            else if(tempBoard[i][j] == 'F'){
                maxF_tiles++;
            }
        } 
    }
    int max, min;

    char maxPlayer, minPlayer;
    if(maxT_tiles > maxF_tiles){
        max = maxT_tiles;
        min = maxF_tiles;
        maxPlayer = 'T';
        minPlayer = 'F';
    }
    else{
        max = maxF_tiles;
        min = maxT_tiles;
        maxPlayer = 'F';
        minPlayer = 'T';
    }
    int heuristicValue;
    vector<Move> maxMoves = tempGame.listMoves(tempBoard, maxPlayer, minPlayer);
    vector<Move> minMoves = tempGame.listMoves(tempBoard, minPlayer, maxPlayer);

    if ( (maxMoves.size() + minMoves.size()) != 0){
        heuristicValue = 100 * (maxMoves.size() - minMoves.size()) / (maxMoves.size() + minMoves.size());
    }
    else{
        heuristicValue = 0;
    }
    return heuristicValue;
}

int checkCorners(vector<vector<char> > const &board, char player){
    int numCorners = 0;
    if(board[0][0] == player){numCorners++;}
    if(board[7][0] == player){numCorners++;}
    if(board[0][7] == player){numCorners++;}
    if(board[7][7] == player){numCorners++;}
    return numCorners;
}

int cornerHeuristic(vector<vector<char> > const &board){
    vector<vector<char> > tempBoard = board;
    int maxT_tiles = 0;
    int maxF_tiles = 0;
    for (int i = 0; i < 8; ++i) { // initialize the board with '-'
        for(int j = 0; j < 8; ++j) {
            if(tempBoard[i][j] == 'T'){
                maxT_tiles++;
            }
            else if(tempBoard[i][j] == 'F'){
                maxF_tiles++;
            }
        } 
    }
    int max, min;

    char maxPlayer, minPlayer;
    if(maxT_tiles > maxF_tiles){
        max = maxT_tiles;
        min = maxF_tiles;
        maxPlayer = 'T';
        minPlayer = 'F';
    }
    else{
        max = maxF_tiles;
        min = maxT_tiles;
        maxPlayer = 'F';
        minPlayer = 'T';
    }
    int heuristicValue;
    int maxCorners = checkCorners(tempBoard, maxPlayer);
    int minCorners = checkCorners(tempBoard, minPlayer);

    if ( (maxCorners + minCorners) != 0){
        heuristicValue = 100 * (maxCorners - minCorners) / (maxCorners + minCorners);
    }
    else{
        heuristicValue = 0;
    }
    return heuristicValue;
}

int maxOfCornerAndParity(vector<vector<char> > const &board){
    int cornerVal = cornerHeuristic(board);
    int parityVal = coinParity(board);
    if (cornerVal > parityVal){
        return cornerVal;
    }
    else{return parityVal;}
}

Move findBestMove(Reversi game, State *state, vector<Move> &moves) {
    int maxHeuristicValue = 0;
    int currentHeuristicValue = 0;
    int indexofMove = 0;
    vector<vector<char>> tempBoard;
    for (int i = 0; i < moves.size(); i++){
        State *tempState = new State(state);
        game.makeMove(tempState, moves.at(i));
        currentHeuristicValue = maxOfCornerAndParity(tempState->getState());
        if (currentHeuristicValue > maxHeuristicValue){
            maxHeuristicValue = currentHeuristicValue;
            indexofMove = i;
        }
        delete tempState;
        tempState = NULL;
    }
    return moves[indexofMove];
}