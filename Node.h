#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <vector>
#include "State.h"
using namespace std;


class Node {

    public:

        State *state; 

        Node *parent;

        vector<Node*> children;

        // Last action made on the board
        Move action;

        int reward;

        int visits;

        Node(State *state);

        Node(State *state, Node *parent, Move action);

        Node();

        ~Node();
};
#endif