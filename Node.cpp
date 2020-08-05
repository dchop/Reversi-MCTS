#include <iostream>
#include <vector>
#include "State.h"
using namespace std;

class Node {

    public:

        State *board; 

        Node *parent;

        vector<Node*> children;

        int reward;

        int visits;

        Node(State *board) {
            this->board = board;
            this->parent = NULL;
            this->reward = 0;
            this->visits = 0;
        }

        Node(State *board, Node *parent) {
            this->board = board;
            this->parent = parent;
            this->reward = 0;
            this->visits = 0;
        }

        
};