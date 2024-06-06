#ifndef DIJ
#define DIJ

#include "dynamicArray.h"
#include "heap.h"
#include "node.h"
#include "nodesp.h"
#include <limits.h>
#include <iostream>
#include <assert.h>

class Dijkstra{
    DynamicArray<int> *resDist;
    DynamicArray<NodeSp> *resNodes;
    int INITDIST = INT_MAX;

    public:
        Dijkstra();
        void spList(DynamicArray<DynamicArray<int>>& list);
        void spMatrix(DynamicArray<DynamicArray<int>>& matrix);
        void getDistTo(int v2);
    private:
        int findMinV(bool added[], int nV);

};

Dijkstra::Dijkstra(){
    resDist = new DynamicArray<int>;
    resNodes = new DynamicArray<NodeSp>;
}

inline void Dijkstra::spList(DynamicArray<DynamicArray<int>> &list){
    //init
    int nV = list.getSize();
    bool added[nV];
    for(int i = 0; i < nV; i++) {
        NodeSp n;
        n.init(i);
        resNodes->add(n);
        resDist->add(INITDIST);
        added[i] = false;
    }

    // dodanie v start
    resDist->get(0) = 0;

    for(int i = 0; i < nV-1; i++) {
        int v = findMinV(added, nV);
        added[v] = true;
        int vDist = resDist->get(v);
        assert(vDist != INITDIST);

        DynamicArray<int> row = list.get(v);

        for(int j = 0; j < row.getSize(); j+=2) {
            int v2 = row.get(j);
            
            if(!added[v2]) {
                int w = row.get(j+1);
                int tempDist = vDist + w;
                if(tempDist < resDist->get(v2)) {
                    resDist->get(v2) = tempDist;
                    resNodes->get(v2).parent = v;
                }
            }
        }        
    }
}

inline void Dijkstra::spMatrix(DynamicArray<DynamicArray<int>> &matrix) {
    //init
    int nV = matrix.getSize();
    bool added[nV];
    for(int i = 0; i < nV; i++) {
        NodeSp n;
        n.init(i);
        resNodes->add(n);
        resDist->add(INITDIST);
        added[i] = false;
    }

    // dodanie v start
    resDist->get(0) = 0;

    for(int i = 0; i < nV-1; i++) {
        int v = findMinV(added, nV);
        added[v] = true;
        int vDist = resDist->get(v);
        assert(vDist != INITDIST);

        // znajdowanie krawedzi v
        DynamicArray<int> row = matrix.get(v);
        for(int ei = 0; ei < row.getSize(); ei++) {
            int w = row.get(ei);
            if(w>0){
                for(int v2 = 0; v2 < nV; v2++) {
                    int w2 = matrix.get(v2).get(ei);
                    if(w2<0) {
                        // krawedz znaleziona
                        if(!added[v2]) {
                            int tempDist = vDist + w;
                            if(tempDist < resDist->get(v2)) {
                                resDist->get(v2) = tempDist;
                                resNodes->get(v2).parent = v;
                            }
                        }
                    }
                }
            }
        }
    }
}

inline void Dijkstra::getDistTo(int v2) {
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

inline int Dijkstra::findMinV(bool added[], int nV) {
    int minV;
    int min = INITDIST;

    for(int v = 0; v < nV; v++) {
        int dist = resDist->get(v);
        if(!added[v] && dist <= min) {
            min = dist;
            minV = v;
        }
    }

    return minV;
}

#endif