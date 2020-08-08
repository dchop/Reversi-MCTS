#include <iostream>
#include <string>
#include <vector>
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

Move mctsPlayer(Reversi game, State *state, char player) {
    Node *root = new Node(state);
    Move bestMove = basicMCTS(root, game, player);
    delete root;

    return bestMove;
}

void startGame() {
    srand(time(0));
    Reversi game;
    State *state = new State();
    Move move1;
    Move move2;
    vector<Move> moves1 = game.listMoves(state->getState(), 'T', 'F');
    vector<Move> moves2 = game.listMoves(state->getState(), 'F', 'T');

    game.printBoard(state->getState());

    while (true) {

        if (moves1.size() > 0) {
            // do {
            //     move1 = inputPlayer();
            //     move1 = game.findMove(moves1, move1);
            // } while (move1.x == -1);
            move1 = randomPlayer(moves1);
            game.makeMove(state, move1);
        }

        // Check if game is over
        moves1 = game.listMoves(state->getState(), 'T', 'F');
        moves2 = game.listMoves(state->getState(), 'F', 'T');
        if (game.checkWin(state->getState(), moves1.size(), moves2.size()))
            break;

        game.printBoard(state->getState());

        if (moves2.size() > 0) {
            // move2 = mctsPlayer(game, state, 'F');
            // move2 = game.findMove(moves2, move2);
            move2 = randomPlayer(moves2);
            game.makeMove(state, move2);
        }

        // Check if game is over
        moves1 = game.listMoves(state->getState(), 'T', 'F');
        moves2 = game.listMoves(state->getState(), 'F', 'T');
        if (game.checkWin(state->getState(), moves1.size(), moves2.size()))
            break;

        game.printBoard(state->getState());
    }

    char winner = game.winningPlayer(state->getState());
    int white, black;
    tie(white, black) = game.score(state->getState());
    delete state;

    printf("Winner: %c\nFinal Score - T:%d F%d\n", winner, white, black);
}

int main() {

    // testListMoves();
    // testNodes();
    startGame();
    
    return 0;
}