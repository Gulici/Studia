#ifndef NODE
#define NODE

#include "dynamicArray.h"
#include "edge.h"

struct Node {
    int index;
    DynamicArray<Edge> *edges;
    bool connected = false;
    Node();
    bool operator==(Node &other);
    // void operator=(Node &other);
};

Node::Node() {
    this->edges = new DynamicArray<Edge>;
}

inline bool Node::operator==(Node &other){
    return index == other.index;
}

// inline void Node::operator=(Node &other) {
//     this->index = other.index;
//     this->edges = other.edges;
// } 



#endif