#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <thread>
#include <chrono>
#include <stdlib.h>
#include "Tests.cpp"

using namespace std;

Move randomPlayer(vector<Move> const &moves) {
    return moves[rand() % moves.size()];
}

Move inputPlayer() {
    int x, y;
    printf("Enter a X Y coordinate: ");
    cin >> x >> y;

    return Move(x,y);
}

Move mctsPlayer(Reversi game, State *state) {
    Node *root = new Node(state);
    Move bestMove = basicMCTS(root, game);
    delete root;

    return bestMove;
}


int coinParity(vector<vector<char> > const &board){
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

void startGame(vector<tuple<char, int, int>> &results, int index) {
    srand(time(0));
    Reversi game;
    State *state = new State();
    Move move1;
    Move move2;
    vector<Move> moves1 = game.listMoves(state->getState(), 'T', 'F');
    vector<Move> moves2 = game.listMoves(state->getState(), 'F', 'T');

    // game.printBoard(state->getState());

    while (true) {

        if (moves1.size() > 0) {
            int maxHeuristicValue = 0;
            int currentHeuristicValue = 0;
            int indexofMove = 0;
            for (int i = 0; i < moves1.size(); i++){
                State *tempState = new State();
                tempState->getState() = state->getState();
                game.makeMove(tempState, moves1.at(i));
                currentHeuristicValue = maxOfCornerAndParity(tempState->getState());
                if (currentHeuristicValue > maxHeuristicValue){
                    maxHeuristicValue = currentHeuristicValue;
                    indexofMove = i;
                }
            }

            // vector<vector<char> > = state->getState();
            // do {
            //     move1 = inputPlayer();
            //     move1 = game.findMove(moves1, move1);
            // } while (move1.x == -1);
            // move1 = randomPlayer(moves1);
            game.makeMove(state, moves1.at(indexofMove));
        }

        // game.printBoard(state->getState());

        // Check if game is over
        moves1 = game.listMoves(state->getState(), 'T', 'F');
        moves2 = game.listMoves(state->getState(), 'F', 'T');
        if (game.checkWin(state->getState(), moves1.size(), moves2.size()))
            break;


        if (moves2.size() > 0) {
            move2 = mctsPlayer(game, state);
            move2 = game.findMove(moves2, move2);
            // printf("Player: %c X:%d Y:%d\n",move2.moveVal, move2.x, move2.y);
            // move2 = randomPlayer(moves2);
            game.makeMove(state, move2);
        }

        // game.printBoard(state->getState());

        // Check if game is over
        moves1 = game.listMoves(state->getState(), 'T', 'F');
        moves2 = game.listMoves(state->getState(), 'F', 'T');
        if (game.checkWin(state->getState(), moves1.size(), moves2.size()))
            break;
    }

    char winner = game.winningPlayer(state->getState());
    int white, black;
    tie(white, black) = game.score(state->getState());
    delete state;
    results[index] = make_tuple(winner, white, black);

    // printf("Winner: %c\nFinal Score - T:%d F:%d\n", winner, white, black);
}

int main() {

    // testListMoves();
    // testNodes();
    char winner;
    int white, black;
    int wWins = 0;
    int bWins = 0;
    int numGames = 50;
    vector<thread> threads;
    vector<tuple<char, int, int>> results(numGames);

    auto start = chrono::high_resolution_clock::now();

    printf("Playing %d games\n", numGames);
    for (int i = 0; i < numGames; i++) {
        threads.push_back(thread(startGame, ref(results), i));
    }

    for (auto &t:threads) {
        if (t.joinable())
            t.join();
    }
    auto end = chrono::high_resolution_clock::now();

    for (auto &res:results) {
        winner = get<0>(res);
        white = get<1>(res);
        black = get<2>(res);
        if (winner == 'T')
            wWins += 1;
        else if (winner == 'F')
            bWins += 1;
        printf("Winner: %c\t\tFinal Score - T:%d F:%d\n", winner, white, black);
    }
    double winP = double(bWins)/double(numGames) * 100;

    printf("whiteWins: %d\t\t blackWins: %d\t\t AI:%.2f%%\n", wWins, bWins, winP);
    auto duration = chrono::duration_cast<chrono::seconds>(end - start);
    std::cout << "Time: " << duration.count() << "s\n";
    
    return 0;
}