#include <iostream>
#include <string>
#include <vector>
#include "Node.h"
#include "Mcts.cpp"

using namespace std;

void testListMoves() {
    State myState;
    Reversi game;
    vector<Move> moves = game.listMoves(myState.getState(), 'T', 'F');
    Move testMove = moves.at(0);

    game.printBoard(myState.getState());

    // make move also calls flippedTiles
    vector<vector <char>> board = game.makeMove(myState.getState(), testMove);

    game.printBoard(board);

    printf("Possible Moves for T:\n");
    for (auto &move: moves) {
        printf("%d, %d\n", move.x, move.y);
    }
}

void testNodes() {
    State *s1 = new State();
    State *s2 = new State();
    State *s3 = new State();
    State *s4 = new State();
    State *s5 = new State();

    Node *n1 = new Node(s1);
    Node *n2 = new Node(s2);
    Node *n3 = new Node(s3);
    Node *n4 = new Node(s4);
    Node *n5 = new Node(s5);

    n3->children.push_back(n4);
    n3->children.push_back(n5);

    n1->children.push_back(n3);
    n1->children.push_back(n2);

    delete n1;
}

int main() {

    // testListMoves();
    testNodes();
    
    return 0;
}