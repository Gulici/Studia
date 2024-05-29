#ifndef GRAPH
#define GRAPH

#include "node.h"
#include "edge.h"
#include "dynamicArray.h"
#include <assert.h>
#include "utils.h"

class Graph {
    DynamicArray<Node> *nodes;
    DynamicArray<Node> *avaibleNodes;
    DynamicArray<Edge> *edges;
    int _size;
    const int minW = 1;
    const int maxW = 10;
    int maxEdgesPerNode;
    int maxEdges;
    bool isDirected = 1;

    public:
        Graph(int size);
        void addEdge(int v1, int v2, int weight);
        void addEdge();
        DynamicArray<Edge>& getEdges();
        void createConnected();
        int** neightMatrix();
};

Graph::Graph(int size) {
    _size = size;
    maxEdgesPerNode = size - 1;
    maxEdges = maxEdgesPerNode * _size;
    nodes = new DynamicArray<Node>;
    edges = new DynamicArray<Edge>;

    for(int i = 0; i < _size; i++) {
        Node n = Node();
        n.index = i;
        nodes->add(n);
    }

    avaibleNodes = nodes->getArray();
}

void Graph::addEdge(int v1,int v2,int weight) {
    assert (v1 >= 0 && v1 < _size);
    assert (v2 >= 0 && v2 < _size);
    
    Node &n1 = nodes->get(v1);   
    Node &n2 = nodes->get(v2);
    Edge e = Edge(v1,v2,weight);

    n1.edges->add(e);
    edges->add(e);
    if(n1.edges->getSize() == maxEdgesPerNode) avaibleNodes->remove(n1);
    n2.connected = true;

    if(!isDirected) {
        Edge e2 = Edge(v2,v1,weight);
        n2.edges->add(e2);
        edges->add(e2);
        if(n2.edges->getSize() == maxEdgesPerNode) avaibleNodes->remove(n2);
        n1.connected = true;
    }
}

void Graph::addEdge() {
    assert(edges->getSize() < maxEdges);

    int v1 = random(0,avaibleNodes->getSize() - 1);
    int v2;

    Node &n = avaibleNodes->get(v1);
    int indexN = n.index;
    DynamicArray<int> connectedToN;
    int nEdgesSize = n.edges->getSize();

    // list of nodes connected to n
    for(int i = 0; i < nEdgesSize; i++) {
        connectedToN.add(n.edges->get(i).getV2());
    }

    // search for proper n2
    bool var;
    do{
        var = false;
        v2 = random(0,_size-1);
        for(int i = 0; i < connectedToN.getSize(); i++) {
            if(v2 == connectedToN.get(i)) {
                var = true;
            }
        }
    }while(indexN==v2 || var);


    int weight = random(minW,maxW);
    addEdge(n.index,v2,weight);
}

DynamicArray<Edge>& Graph::getEdges() {
    return *edges;  
}

// func. creating random path in graph - making connected graph
inline void Graph::createConnected() {
    DynamicArray<Node> unconnected = *(nodes->getArray());
    DynamicArray<Node> connected;

    int unconSize = unconnected.getSize();
    int conSize = 0;

    // picking 1st node
    Node cN = unconnected.get(0);
    connected.add(cN);
    unconnected.removeAt(0);
    unconSize--;
    conSize++;

    // creating path
    while(unconSize > 0) {
        int conIndex = random(0,conSize-1);
        int unconIndex = random(0,unconSize-1);

        Node e1 = connected.get(conIndex);
        Node e2 = unconnected.get(unconIndex);
        int weight = random(minW,maxW);

        addEdge(e1.index,e2.index,weight);

        connected.add(e2);
        unconnected.removeAt(unconIndex);
        conSize++;
        unconSize--;
    }
}

int** Graph::neightMatrix()
{   
    int** matrix = new int*[_size];
    for(int i = 0; i < _size; i++) {
        DynamicArray<Edge> *iedges = nodes->get(i).edges;

        matrix[i] = new int[_size];
        for(int j = 0; j < _size; j++) {
            matrix[i][j] = 0;
        }

        for(int j = 0; j < iedges->getSize(); j++) {
            Edge e = iedges->get(j);
            int v2 = e.getV2();
            matrix[i][v2] = e.getWeight();
        }
    }

    return matrix;
}

#endif