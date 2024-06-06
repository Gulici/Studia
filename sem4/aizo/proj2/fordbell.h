#ifndef FORD
#define FORD

#include "dynamicArray.h"
#include "heap.h"
#include "node.h"
#include "nodesp.h"
#include <limits.h>
#include <iostream>
#include <assert.h>

class FordBell{
    DynamicArray<int> *resDist;
    DynamicArray<NodeSp> *resNodes;
    DynamicArray<Edge> *edges;
    int INITDIST = INT_MAX;

    public:
        FordBell();
        void spList(DynamicArray<DynamicArray<int>>& list);
        void spMatrix(DynamicArray<DynamicArray<int>>& matrix);
        void getDistTo(int v2);
};

FordBell::FordBell() {
    resDist = new DynamicArray<int>;
    resNodes = new DynamicArray<NodeSp>;
    edges = new DynamicArray<Edge>;
}

inline void FordBell::spList(DynamicArray<DynamicArray<int>> &list) {
    int nV = list.getSize();
    //utworzenie listy krawedzi
    for(int vi = 0; vi < nV; vi++) {
        DynamicArray<int> row = list.get(vi);
        for(int j = 0; j < row.getSize(); j+=2) {
            int v2 = row.get(j);
            int w = row.get(j+1);
            Edge e = Edge(vi,v2,w);
            edges->add(e);
        }
    }
    int nE = edges->getSize();

    //inicjalizacja
    for(int i = 0; i < nV; i++) {
        NodeSp n;
        n.init(i);
        resNodes->add(n);
        resDist->add(INITDIST);
    }

    // dodanie v start
    resDist->get(0) = 0;

    // relaksacja krawedzi nV-1 razy
    for(int i = 0; i< nV-1; i++) {
        for(int j = 0; j < nE; j++) {
            Edge e = edges->get(j);
            int v1 = e.getV1();
            int v2 = e.getV2();
            int w = e.getWeight();

            int v1dist = resDist->get(v1);

            //czy v1 zostalo zrelaksowane i czy zrelaksowac v2
            if(v1dist != INITDIST) {
                int tempW = v1dist + w;
                if (resDist->get(v2) > tempW){
                    resDist->get(v2) = tempW;
                    resNodes->get(v2).parent = v1;
                }
            }
        }
    }

    //sprawdzenie czy nie wystepuja negatywne cykle
    for(int j = 0; j < nE; j++) {
        Edge e = edges->get(j);
        int v1 = e.getV1();
        int v2 = e.getV2();
        int w = e.getWeight();

        int v1dist = resDist->get(v1);

        //czy v1 zostalo zrelaksowane i czy zrelaksowac v2
        if(v1dist != INITDIST) {
            int tempW = v1dist + w;
            if (resDist->get(v2) > tempW){
                std::cout<<"Znaleziono negatywny cykl\n";
                return;
            }
        }
    }
}

inline void FordBell::spMatrix(DynamicArray<DynamicArray<int>> &matrix){
    int nV = matrix.getSize();
    int nE = matrix.get(0).getSize();
    //utworzenie listy krawedzi
    for(int ei = 0; ei < nE; ei++) {
        int v1,v2,w;
        for(int vi = 0; vi < nV; vi++) {
            int temp = matrix.get(vi).get(ei);
            if(temp == 0) continue;
            else if(temp > 0) {
                w = temp;
                v1 = vi;
            }
            else v2 = vi;
        }
        Edge e = Edge(v1,v2,w);
        edges->add(e);
    }

    //inicjalizacja
    for(int i = 0; i < nV; i++) {
        NodeSp n;
        n.init(i);
        resNodes->add(n);
        resDist->add(INITDIST);
    }

    // dodanie v start
    resDist->get(0) = 0;

    // relaksacja krawedzi nV-1 razy
    for(int i = 0; i< nV-1; i++) {
        for(int j = 0; j < nE; j++) {
            Edge e = edges->get(j);
            int v1 = e.getV1();
            int v2 = e.getV2();
            int w = e.getWeight();

            int v1dist = resDist->get(v1);

            //czy v1 zostalo zrelaksowane i czy zrelaksowac v2
            if(v1dist != INITDIST) {
                int tempW = v1dist + w;
                if (resDist->get(v2) > tempW){
                    resDist->get(v2) = tempW;
                    resNodes->get(v2).parent = v1;
                }
            }
        }
    }

    //sprawdzenie czy nie wystepuja negatywne cykle
    for(int j = 0; j < nE; j++) {
        Edge e = edges->get(j);
        int v1 = e.getV1();
        int v2 = e.getV2();
        int w = e.getWeight();

        int v1dist = resDist->get(v1);

        //czy v1 zostalo zrelaksowane i czy zrelaksowac v2
        if(v1dist != INITDIST) {
            int tempW = v1dist + w;
            if (resDist->get(v2) > tempW){
                std::cout<<"Znaleziono negatywny cykl\n";
                return;
            }
        }
    }
}

inline void FordBell::getDistTo(int v2) {
    std::cout << "Dystans do " << v2 << ": " << resDist->get(v2) << '\n';
    DynamicArray<int> path;
    NodeSp currV = resNodes->get(v2);
    while(currV.parent != -1) {
        path.insert(currV.index,0);
        currV = resNodes->get(currV.parent);
        if(currV.index == 0) path.insert(currV.index,0);
    }
    for(int i = 0; i < path.getSize(); i++) {
        if(i == 0) std::cout << path.get(i);
        else std::cout << " --> " << path.get(i);
    }
    std::cout<<'\n';
}

#endif