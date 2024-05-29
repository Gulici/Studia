#include <iostream>
#include "dynamicArray.h"
#include "heap.h"
#include "graph.h"
#include "edge.h"

int main() {

    Graph g = Graph(2);
    g.createConnected();

    DynamicArray<Edge> &edges = g.getEdges();

    for (int i = 0; i < edges.getSize(); i++) {
        std::cout << edges.get(i) << '\n';
    }

    std::cout<<std::endl;

    g.addEdge();

    return 0;
}