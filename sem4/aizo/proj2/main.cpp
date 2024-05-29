#include <iostream>
#include "dynamicArray.h"
#include "heap.h"
#include "graph.h"
#include "edge.h"

int main() {
    int gsize = 6;
    Graph g = Graph(gsize);
    DynamicArray<Edge> &edges = g.getEdges();
    g.createConnected();

    for (int i = 0; i < edges.getSize(); i++) {
        std::cout << edges.get(i) << '\n';
    }
    std::cout<< '\n';


    int** matrix  = g.neightMatrix();

    for(int i = 0; i < gsize; i++) {
        for(int j  = 0; j < gsize; j++) {
            std::cout<<matrix[i][j]<<' ';
        }
        std::cout<< '\n';
    }

    for(int i = 0; i < gsize*(gsize-1)-(gsize-1); i++) {
        g.addEdge();
    }

    std::cout<< '\n';
    matrix = g.neightMatrix();
    for(int i = 0; i < gsize; i++) {
        for(int j  = 0; j < gsize; j++) {
            std::cout<<matrix[i][j]<<' ';
        }
        std::cout<<std::endl;
    }

    return 0;
}