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
    const int maxW = 1000000;
    int maxEdgesPerNode;
    int maxEdges;
    bool isDirected = true;

    public:
        Graph(int size);
        Graph(int size, int fill, bool directed);
        Graph(DynamicArray<DynamicArray<int>> data, bool isDirected);
        void addEdge(int v1, int v2, int weight);
        void addEdge();
        DynamicArray<Edge>& getEdges();
        void createConnected();
        int** neighMatrix();
        DynamicArray<DynamicArray<int>>& neighList();
        DynamicArray<DynamicArray<int>>& incidenceMatrix();
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

inline Graph::Graph(int size, int fill, bool directed) {
    isDirected = directed;
    
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

    createConnected();
    maxEdges=maxEdges*((float)fill/100);

    int edgesToAdd = maxEdges - edges->getSize();

    for(int i = 0; i < edgesToAdd; i++) {
        this->addEdge();
        if(!isDirected) i++;
    }

    delete avaibleNodes;
}

inline Graph::Graph(DynamicArray<DynamicArray<int>> data, bool isDirected) {
    DynamicArray<int> row = data.get(0);
    int nE = row.get(0);
    int nV = row.get(1);
    this->isDirected = isDirected;

    _size = nV;
    nodes = new DynamicArray<Node>;
    edges = new DynamicArray<Edge>;

    for(int i = 0; i < _size; i++) {
        Node n = Node();
        n.index = i;
        nodes->add(n);
    }

    for(int i = 1; i <= nE; i++) {
        row = data.get(i);
        int v1 = row.get(0);
        int v2 = row.get(1);
        int weight = row.get(2);
        Edge e = Edge(v1,v2,weight);
        addEdge(v1,v2,weight);
    }
}

void Graph::addEdge(int v1,int v2,int weight) {
    assert (v1 >= 0 && v1 < _size);
    assert (v2 >= 0 && v2 < _size);
    
    Node &n1 = nodes->get(v1);   
    Node &n2 = nodes->get(v2);
    Edge e = Edge(v1,v2,weight);

    n1.edges.add(e);
    edges->add(e);
    if(n1.edges.getSize() == maxEdgesPerNode) avaibleNodes->remove(n1);
    n2.connected = true;

    if(!isDirected) {
        Edge e2 = Edge(v2,v1,weight);
        n2.edges.add(e2);
        edges->add(e2);
        if(n2.edges.getSize() == maxEdgesPerNode) avaibleNodes->remove(n2);
        n1.connected = true;
    }
}

void Graph::addEdge() {
    assert(edges->getSize() < maxEdges);

    int v1 = random(0,avaibleNodes->getSize() - 1);
    int v2;

    Node temp = avaibleNodes->get(v1);
    int indexN = temp.index;
    Node n = nodes -> get(indexN);
    DynamicArray<int> connectedToN;
    int nEdgesSize = n.edges.getSize();

    // list of nodes connected to n
    for(int i = 0; i < nEdgesSize; i++) {
        connectedToN.add(n.edges.get(i).getV2());
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

        Node &e1 = connected.get(conIndex);
        Node &e2 = unconnected.get(unconIndex);
        int weight = random(minW,maxW);

        addEdge(e1.index,e2.index,weight);

        connected.add(e2);
        unconnected.removeAt(unconIndex);
        conSize++;
        unconSize--;
    }
}

int** Graph::neighMatrix()
{   
    int** matrix = new int*[_size];
    for(int i = 0; i < _size; i++) {
        DynamicArray<Edge> iedges = nodes->get(i).edges;

        matrix[i] = new int[_size];
        for(int j = 0; j < _size; j++) {
            matrix[i][j] = 0;
        }

        for(int j = 0; j < iedges.getSize(); j++) {
            Edge e = iedges.get(j);
            int v2 = e.getV2();
            matrix[i][v2] = e.getWeight();
        }
    }

    return matrix;
}

inline DynamicArray<DynamicArray<int>>&Graph::neighList(){
    DynamicArray<DynamicArray<int>> *list = new DynamicArray<DynamicArray<int>>;

    for(int i = 0; i < _size; i++) {
        DynamicArray<Edge> iedges = nodes->get(i).edges;
        int rowSize = iedges.getSize();
        DynamicArray<int> row;
        for(int j = 0; j < rowSize; j++) {
            Edge e = iedges.get(j);
            int v2 = e.getV2();
            int weight = e.getWeight();
            row.add(v2);
            row.add(weight);
        }
        list->add(row);
    }

    return *list;
}

inline DynamicArray<DynamicArray<int>> &Graph::incidenceMatrix()
{   
    int val = 0;
    DynamicArray<DynamicArray<int>> *matrix = new DynamicArray<DynamicArray<int>>;
    int rowSize = edges->getSize();
    //zapelnienie macierzy zerami
    for(int i = 0; i < _size; i++) {
        DynamicArray<int> row;
        for(int j = 0; j < rowSize; j++) {
            row.add(val);
        }
        matrix->add(row);
    }

    //dodanie krawedzi do macierzy
    for(int i = 0; i < rowSize; i++) {
        Edge e = edges->get(i);
        int v1 = e.getV1();
        int v2 = e.getV2();
        int weight = e.getWeight();
        matrix->get(v1).get(i) = weight;
        matrix->get(v2).get(i) = -weight;
    }

    // //proba z dodawaniem krawedzi od wierzcholkow
    // int added = 0;
    // for(int i = 0; i < nodes->getSize(); i++){
    //     DynamicArray<Edge> *vedges = nodes->get(i).edges;
        
    //     for(int j = 0; j < vedges->getSize(); j++) {
    //         Edge e = vedges->get(j);
    //         int v2 = e.getV2();
    //         int w = e.getWeight();
    //         matrix->get(i).get(added) = w;
    //         matrix->get(v2).get(added) = -w;
    //         added++;
    //     }
    // }

    return *matrix;
}

#endif