#ifndef NODESP
#define NODESP

struct NodeSp{
    int index;
    int parent;

    void init(int index) {
        this->index = index;
        parent = -1;
    }
};

#endif