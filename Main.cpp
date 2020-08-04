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

    game.printBoard(myState.getState());

    printf("Possible Moves for T:\n");
    for (auto &move: moves) {
        printf("%d, %d\n", move.x, move.y);
    }
}

int main() {

    testListMoves();
    
    return 0;
}