#include <iostream>
#include <string>
#include <vector>
#include "Reversi.h"
#include "State.h"

using namespace std;

void testListMoves() {
    State myState;
    Reversi game;
    vector<Move> moves = game.listMoves(myState.getState(), 'T', 'F');
    Move testMove = moves.at(0);

    game.printBoard(myState.getState());
    // Call make move function which will call flipPieces function
    vector<vector <char>> board = game.makeMove(myState.getState(), testMove);
    // game.flipPieces(myState.getState(), testMove);
    game.printBoard(board);

    printf("Possible Moves for T:\n");
    for (auto &move: moves) {
        printf("%d, %d\n", move.x, move.y);
    }
}

int main() {

    testListMoves();
    
    return 0;
}