#ifndef PRIM
#define PRIM

#include "dynamicArray.h"
#include "heap.h"
#include "node.h"
#include <iostream>

class Prim {
    DynamicArray<int> *nodes;
    DynamicArray<Edge> *edges;
    Heap<Edge> *heap;

    public:
        Prim();
        void mstList(DynamicArray<DynamicArray<int>>& list);
        void mstMatrix(DynamicArray<DynamicArray<int>>& matrix);
        void addEdgesList(DynamicArray<DynamicArray<int>>& list, int v);
        void addEdgesMatrix(DynamicArray<DynamicArray<int>>& matrix, int v, int vNum);
        void print();
};


Prim::Prim(){}

inline void Prim::mstList(DynamicArray<DynamicArray<int>> &list){
    nodes = new DynamicArray<int>;
    edges = new DynamicArray<Edge>;
    heap = new Heap<Edge>;

    //wybranie wierzcholka poczatkowego
    int v = 0;
    nodes->add(v);
    int vNum = list.getSize();

    //inicjalizacja - dodanie krawedzi vstart do heap
    addEdgesList(list, v);

    //petla do czasu gdy wszystkie wierzcholki nie dodane do mst
    while(nodes->getSize() < vNum){
        //znajdowanie odpowiedniej krawedzi
        bool isCycle = true;
        while(isCycle && heap->getSize()>0) {
            // znajdz krawedz o najmniejszej wadze
            Edge e = heap->getFirst();
            heap->pop();
            int v2 = e.getV2();
            isCycle = false;
            //sprawdz czy nie tworzy cyklu
            for(int i = 0; i < nodes->getSize(); i++) {
                int vAdded = nodes->get(i);
                if(v2 == vAdded) {
                    isCycle = true;
                    break;
                } 
            }
            // dodaj jesli nie tworzy cyklu
            if(!isCycle) {
                nodes->add(v2);
                edges->add(e);
                addEdgesList(list, v2);
            }
        }        
    }
}

inline void Prim::mstMatrix(DynamicArray<DynamicArray<int>> &matrix){
    nodes = new DynamicArray<int>;
    edges = new DynamicArray<Edge>;
    heap = new Heap<Edge>;

    //wybranie wierzcholka poczatkowego
    int v = 0;
    nodes->add(v);
    int vNum = matrix.getSize();

    //inicjalizacja - dodanie krawedzi vstart do heap
    addEdgesMatrix(matrix, v, vNum);

    //petla do czasu gdy wszystkie wierzcholki nie dodane do mst
    while(nodes->getSize() < vNum){
        //znajdowanie odpowiedniej krawedzi
        bool isCycle = true;
        while(isCycle && heap->getSize()>0) {
            // znajdz krawedz o najmniejszej wadze
            Edge e = heap->getFirst();
            heap->pop();
            int v2 = e.getV2();
            isCycle = false;
            //sprawdz czy nie tworzy cyklu
            for(int i = 0; i < nodes->getSize(); i++) {
                int vAdded = nodes->get(i);
                if(v2 == vAdded) {
                    isCycle = true;
                    break;
                } 
            }
            // dodaj jesli nie tworzy cyklu
            if(!isCycle) {
                nodes->add(v2);
                edges->add(e);
                addEdgesMatrix(matrix, v2, vNum);
            }
        }        
    }    
}

inline void Prim::addEdgesList(DynamicArray<DynamicArray<int>>& list, int v){
    DynamicArray<int> row = list.get(v);
    int eNum = row.getSize()/2;
    for(int i = 0; i < eNum; i++) {
        int index = i*2;
        int v2 = row.get(index);
        int weight = row.get(index+1);
        Edge e = Edge(v,v2,weight);
        heap->push(e);
    }
}

inline void Prim::addEdgesMatrix(DynamicArray<DynamicArray<int>> &matrix, int v, int vNum){
    DynamicArray<int> row = matrix.get(v);;
    //znajdz poczatek krawedzi
    for(int i = 0; i < row.getSize(); i++) {
        int weight = row.get(i);
        if(weight > 0) {
            // znajdz koniec krawedzi
            int weight2 = 0;
            for(int j = 0; j < vNum; j++) {
                weight2 = matrix.get(j).get(i);
                if(weight2 < 0) {
                    Edge e = Edge(v,j,weight);
                    heap->push(e);
                    break; 
                }
            }
        }
    }
}

inline void Prim::print(){
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