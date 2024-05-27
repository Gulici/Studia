#include <iostream>
#include "dynamicArray.h"
#include "heap.h"
#include "edge.h"

int main() {
    DynamicArray<int> arr;
    arr.add(2);
    std::cout << arr.get(0) << std::endl;

    Edge e1 = Edge(0,1,5);
    Edge e2 = Edge(0,1,1);
    Edge e3 = Edge(0,1,2);
    Edge e4 = Edge(0,1,3);

    Heap<Edge> heap;
    heap.push(e1);
    heap.push(e2);
    heap.push(e3);
    heap.push(e4);

    while(heap.getSize() > 0) {
        Edge t = heap.getFirst();
        t.print();
        heap.pop();
    }

    return 0;
}