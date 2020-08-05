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

        Node(State *state) {
            this->state = state;
            this->parent = NULL;
            this->reward = 0;
            this->visits = 0;
        }

        Node(State *state, Node *parent) {
            this->state = state;
            this->parent = parent;
            this->reward = 0;
            this->visits = 0;
        }

        
};