#include <iostream>
#include <vector>
#include "Node.h"
using namespace std;


Node::Node(State *state) {
    this->state = state;
    this->parent = NULL;
    this->action = Move(-1,-1);
    this->reward = 0;
    this->visits = 0;
}

Node::Node(State *state, Node *parent, Move action) {
    this->state = state;
    this->parent = parent;
    this->action = action;
    this->reward = 0;
    this->visits = 0;
}

Node::Node() {
    this->state = NULL;
    this->parent = NULL;
    this->action = Move(-1,-1);
    this->reward = 0;
    this->visits = 0;
}

Node::~Node() {

    // Need to delete the children as well
    if (this->children.size() > 0) {
        for (auto &child: children) {
            delete child->state;
            delete child;
        }
    }

}