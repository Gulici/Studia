#ifndef KRUS
#define KRUS

#include "dynamicArray.h"
#include "heap.h"
#include "node.h"
#include <iostream>

class Kruskal {
    DynamicArray<int> *nodes;
    DynamicArray<Edge> *edges;
    Heap<Edge> *heap;

    public:
        Kruskal();
        void mstList(DynamicArray<DynamicArray<int>>& list);
        void mstMatrix(DynamicArray<DynamicArray<int>>& matrix);
        void print();

};

class UnionFind {
    int* parent;
    int* rank;

    public:
        UnionFind(int n);
        int find(int i);
        void unite(int x, int y);
};

Kruskal::Kruskal(){
    nodes = new DynamicArray<int>;
    edges = new DynamicArray<Edge>;
    heap = new Heap<Edge>;
}

inline void Kruskal::mstList(DynamicArray<DynamicArray<int>> &list) {
    //utworzenie listy krawedzi i dodanie do stosu
    int vNum = list.getSize();
    for(int v1 = 0; v1 < vNum; v1++) {
        DynamicArray<int> row = list.get(v1);
        int eNum = row.getSize()/2;
        for(int i = 0; i < eNum; i++) {
            int index = i*2;
            int v2 = row.get(index);
            int weight = row.get(index+1);
            Edge e = Edge(v1,v2,weight);
            heap->push(e);
        }        
    }

    UnionFind ufAlg(vNum);
    while(edges->getSize() < vNum-1) {
        Edge e = heap->getFirst();
        heap->pop();

        //sprawdzenie czy v1 i v2 naleza do roznych podrzew
        int v1 = e.getV1();
        int v2 = e.getV2();
        if(ufAlg.find(v1) != ufAlg.find(v2)) {
            ufAlg.unite(v1,v2);
            edges->add(e);
        }
    }
}

inline void Kruskal::mstMatrix(DynamicArray<DynamicArray<int>> &matrix) {
    //utworzenie listy krawedzi i dodanie do stosu
    DynamicArray<Edge> etemp;
    int vNum = matrix.getSize();
    int eNum = matrix.get(0).getSize();
    for(int ei = 0; ei < eNum; ei++) {
        int v1,v2,w;
        for(int vi = 0; vi<vNum; vi++) {
            int temp = matrix.get(vi).get(ei);
            if(temp == 0) continue;
            else if(temp > 0) {
                w = temp;
                v1 = vi;
            }
            else v2 = vi;
        }
        Edge e = Edge(v1,v2,w);
        etemp.add(e);
        heap->push(e);
    }

    UnionFind ufAlg(vNum);

    // TODO: NIE ZNAJDUJE MST - HEAP SIE KONCZY
    while(edges->getSize() < vNum-1 && heap->getSize()>0) {
        Edge e = heap->getFirst();
        heap->pop();

        //sprawdzenie czy v1 i v2 naleza do roznych podrzew
        int v1 = e.getV1();
        int v2 = e.getV2();
        if(ufAlg.find(v1) != ufAlg.find(v2)) {
            ufAlg.unite(v1,v2);
            edges->add(e);
        }
    }
}

UnionFind::UnionFind(int n){
    parent = new int[n];
    rank = new int[n];

    for(int i = 0; i < n; i++) {
        parent[i] = -1;
        rank[i] = 1;
    }
}

inline int UnionFind::find(int i) {
    if (parent[i] == -1) 
        return i; 
  
    return parent[i] = find(parent[i]); 
}

inline void UnionFind::unite(int x, int y) {
    int s1 = find(x);
    int s2 = find(y);

    if(s1 != s2) {
        if(rank[s1] < rank[s2]) parent[s1] = s2;
        else if(rank[s1] > rank[s2]) parent[s2] = s1;
        else {
            parent[s2] = s1;
            rank[s1] += 1;
        }
    }
}

inline void Kruskal::print(){
    int sumWeight = 0;
    for(int i = 0; i < edges->getSize(); i++) {
        Edge e = edges->get(i);
        std::cout << e;
        sumWeight += e.getWeight();
    } 
    std::cout<<"\nWaga sciezki: " << sumWeight <<'\n'; 
    std::cout<<"Nedges: " << edges->getSize() <<'\n'; 
}

#endif