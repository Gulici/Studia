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
    const int minW = 0;
    const int maxW = 10;
    int maxEdgesPerNode;
    int maxEdges;
    bool isDirected = false;

    public:
        Graph(int size);
        void addEdge(int v1, int v2, int weight);
        void addEdge();
        DynamicArray<Edge>& getEdges();
        void createConnected();

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
    
    //zamienic na wskazniki na node
    Node n1 = nodes->get(v1);   
    Node n2 = nodes->get(v2);
    Edge e = Edge(v1,v2,weight);

    n1.edges->add(e);
    edges->add(e);
    if(n1.edges->getSize() == maxEdgesPerNode) {
        avaibleNodes->remove(n1);
    }
    n2.connected = true;        //istnieje sciezka do v2

    if(!isDirected) {
        Edge e2 = Edge(v2,v1,weight);
        n2.edges->add(e2);
        edges->add(e2);
        if(n2.edges->getSize() == maxEdgesPerNode) avaibleNodes->remove(n2);
        n1.connected = true;    //istnieje sciezka do v1
    }
}

void Graph::addEdge() {
    // czy mozna jeszcze dodac kolejna krawedz
    assert(edges->getSize() < maxEdges);

    //losowanie wierzcholka z talicy dostepnych
    int v1 = random(0,avaibleNodes->getSize() - 1);
    int v2;

    Node n = nodes->get(v1);
    DynamicArray<Edge> *NEdges = n.edges;
    DynamicArray<int> connectedToN;

    for(int i = 0; i < NEdges->getSize(); i++) {
        connectedToN.add(NEdges->get(i).getV2());
    }

    bool var = false;
    do{
        var = false;
        v2 = random(0,_size-1);
        for(int i = 0; i < connectedToN.getSize(); i++) {
            if(v2 == connectedToN.get(i)) {
                var = true;
            }
        }
    }while(v1==v2 || var);


    int weight = random(minW,maxW);
    addEdge(v1,v2,weight);
}

DynamicArray<Edge>& Graph::getEdges() {
    return *edges;  
}

inline void Graph::createConnected() {
    DynamicArray<Node> unconnected = *(nodes->getArray());
    DynamicArray<Node> connected;

    int unconSize = unconnected.getSize();
    int conSize = 0;

    int i = random(0, unconSize-1);
    Node cN = unconnected.get(i);
    connected.add(cN);
    unconnected.removeAt(i);
    unconSize--;
    conSize++;

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

#endif