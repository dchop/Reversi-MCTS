#include <iostream>
#include <vector>
#include "Node.h"
using namespace std;


Node::Node(State *state) {
    this->state = state;
    this->parent = NULL;
    this->reward = 0;
    this->visits = 0;
}

Node::Node(State *state, Node *parent) {
    this->state = state;
    this->parent = parent;
    this->reward = 0;
    this->visits = 0;
}

Node::Node() {
    this->state = NULL;
    this->parent = NULL;
    this->reward = 0;
    this->visits = 0;
}

Node::~Node() {

    // Delete the root state
    delete this->state;

    // Need to delete the children as well
    if (this->children.size() > 0) {
        for (auto &child: children) {
            delete child;
        }
    }

}