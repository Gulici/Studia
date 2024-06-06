#include <iostream>
#include <chrono>
#include "dynamicArray.h"
#include "heap.h"
#include "graph.h"
#include "edge.h"
#include "prim.h"
#include "kruskal.h"
#include "dijkstra.h"
#include "fordbell.h"

int main() {
    //maksymalna ilosc wierzcholkow 500 
    int gsize = 500;
    Graph g = Graph(gsize, 25, true);
    std::cout<<g.getEdges().getSize()<<'\n';

    DynamicArray<DynamicArray<int>> &list = g.neighList();
    DynamicArray<DynamicArray<int>> &matrix = g.incidenceMatrix();

    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    auto tms = std::chrono::duration_cast<std::chrono::milliseconds>(diff);

    // kazde MST dziala, dynamiczna tablica jest problemem!
    
    // Prim p;
    // start = std::chrono::high_resolution_clock::now();
    // p.mstList(list);
    // end = std::chrono::high_resolution_clock::now();
    // std::chrono::duration<double> diff = end - start;
    // tms = std::chrono::duration_cast<std::chrono::milliseconds>(diff);
    // p.print();
    // std::cout << "Czas: " << tms.count() << std::endl;

    // Prim pM;
    // start = std::chrono::high_resolution_clock::now();
    // pM.mstMatrix(matrix);
    // end = std::chrono::high_resolution_clock::now();
    // diff = end - start;
    // tms = std::chrono::duration_cast<std::chrono::milliseconds>(diff);
    // pM.print();
    // std::cout << "Czas: " << tms.count() << std::endl; 

    // Kruskal k;
    // start = std::chrono::high_resolution_clock::now();
    // k.mstList(list);
    // end = std::chrono::high_resolution_clock::now();\
    // diff = end-start;
    // tms = std::chrono::duration_cast<std::chrono::milliseconds>(diff);
    // k.print();
    // std::cout << "Czas: " << tms.count() << std::endl;

    // Kruskal k2;
    // start = std::chrono::high_resolution_clock::now();
    // k2.mstMatrix(matrix);
    // end = std::chrono::high_resolution_clock::now();
    // diff = end-start;
    // tms = std::chrono::duration_cast<std::chrono::milliseconds>(diff);
    // k2.print();
    // std::cout << "Czas: " << tms.count() << std::endl;

    Dijkstra d;
    start = std::chrono::high_resolution_clock::now();
    d.spList(list);
    end = std::chrono::high_resolution_clock::now();
    diff = end-start;
    tms = std::chrono::duration_cast<std::chrono::milliseconds>(diff);
    std::cout << "Czas: " << tms.count() << std::endl;
    // for(int i = 1; i < gsize; i++) {
    //     d.getDistTo(i);
    // }

    Dijkstra d2;
    start = std::chrono::high_resolution_clock::now();
    d2.spMatrix(matrix);
    end = std::chrono::high_resolution_clock::now();
    diff = end-start;
    tms = std::chrono::duration_cast<std::chrono::milliseconds>(diff);
    std::cout << "Czas: " << tms.count() << std::endl;
    // for(int i = 1; i < gsize; i++) {
    //     d2.getDistTo(i);
    // }

    FordBell f1;
    start = std::chrono::high_resolution_clock::now();
    f1.spList(list);
    end = std::chrono::high_resolution_clock::now();
    diff = end-start;
    tms = std::chrono::duration_cast<std::chrono::milliseconds>(diff);
    std::cout << "Czas: " << tms.count() << std::endl;
    // for(int i = 1; i < gsize; i++) {
    //     f1.getDistTo(i);
    // }

    FordBell f2;
    start = std::chrono::high_resolution_clock::now();
    f2.spMatrix(matrix);
    end = std::chrono::high_resolution_clock::now();
    diff = end-start;
    tms = std::chrono::duration_cast<std::chrono::milliseconds>(diff);
    std::cout << "Czas: " << tms.count() << std::endl;
    // for(int i = 1; i < gsize; i++) {
    //     f2.getDistTo(i);
    // }


    // for(int i = 0; i < matrix.getSize(); i++) {
    //     DynamicArray<int> &row = matrix.get(i);
    //     for(int j = 0; j < row.getSize(); j++) {
    //         std::cout << row.get(j) << '\t';
    //     }
    //     std::cout<<'\n';
    // }

    // for(int i = 0; i < list.getSize(); i++) {
    //     DynamicArray<int> &row = list.get(i);
    //     for(int j = 0; j < row.getSize(); j++) {
    //         std::cout << row.get(j) << ' ';
    //     }
    //     std::cout<<'\n';
    // }
    
    return 0;
}