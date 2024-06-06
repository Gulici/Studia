#ifndef NODE
#define NODE

#include "dynamicArray.h"
#include "edge.h"

struct Node {
    int index;
    DynamicArray<Edge> edges;
    bool connected = false;
    Node();
    ~Node();
    bool operator==(Node &other);
};

Node::Node() {
}

Node::~Node() {
}

inline bool Node::operator==(Node &other){
    return index == other.index;
}




#endif