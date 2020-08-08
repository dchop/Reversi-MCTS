#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include "Tests.cpp"

using namespace std;

Move inputPlayer(Reversi game, State *state, char player) {
    int x, y;

    printf("Enter a X Y coordinate: ");
    cin >> x >> y;

    return Move(x,y);
}

Move mctsPlayer(Reversi game, State *state, char player) {
    Node *root = new Node(state);
    Move bestMove = basicMCTS(root, game, player);
    delete root;

    return bestMove;
}

char startGame() {
    Reversi game;
    State *state = new State();
    Move move1;
    Move move2;
    vector<Move> moves1 = game.listMoves(state->getState(), 'T', 'F');
    vector<Move> moves2;

    game.printBoard(state->getState());

    while (true) {

        if (moves1.size() > 0) {
            do {
                move1 = inputPlayer(game, state, 'T');
                move1 = game.findMove(moves1, move1);
            } while (move1.x == -1);
            game.makeMove(state, move1);
        }

        // Check if game is over
        moves1 = game.listMoves(state->getState(), 'T', 'F');
        moves2 = game.listMoves(state->getState(), 'F', 'T');
        if (game.checkWin(state->getState(), moves1.size(), moves2.size())) {
            break;
        }

        game.printBoard(state->getState());

        if (moves2.size() > 0) {
            move2 = mctsPlayer(game, state, 'F');
            move2 = game.findMove(moves2, move2);
            game.makeMove(state, move2);
        }

        // Check if game is over
        moves1 = game.listMoves(state->getState(), 'T', 'F');
        moves2 = game.listMoves(state->getState(), 'F', 'T');
        if (game.checkWin(state->getState(), moves1.size(), moves2.size())) {
            break;
        }

        game.printBoard(state->getState());
    }

    return 'T';
}

int main() {

    // testListMoves();
    // testNodes();
    char winner = startGame();
    
    return 0;
}