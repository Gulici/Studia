#include <iostream>
#include "dynamicArray.h"
#include "heap.h"
#include "edge.h"

int main() {
    DynamicArray<int> arr;
    arr.add(2);
    std::cout << arr.get(0) << std::endl;

    Heap<Edge> heap;
    for(int i = 200; i > 0; i--) {
        Edge e = Edge(0,0,i);
        heap.push(e);
    }

    DynamicArray<Edge> edgeArr = heap.getArr();

    for(int i = 0; i < edgeArr.getSize(); i++) {
        Edge e = edgeArr.get(i);
        e.print();
    }

    std::cout<<std::endl;

    while(heap.getSize() > 0) {
        Edge t = heap.getFirst();
        t.print();
        heap.pop();
    }

    return 0;
}