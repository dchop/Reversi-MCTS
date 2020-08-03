#include <iostream>
#include <string>
#include <vector>
#include "Reversi.h"
#include "State.h"

using namespace std;

void testListMoves() {
    State myState;
    vector<Move> moves = myState.listMoves('T', 'F');

    printf("Possible Moves:\n");
    for (auto &move: moves) {
        printf("%d, %d\n", move.x, move.y);
    }

}

int main() {

    // Reversi newBoard;
    // newBoard.printBoard();

    testListMoves();

    
    return 0;
}