#ifndef HEAP
#define HEAP
#include "dynamicArray.h"

template <class T>
class Heap {
    DynamicArray<T> queue;
    int last;

    public:
        Heap();
        // ~Heap();
        T getFirst();
        void push (T element);
        void pop();
        int getSize();
        DynamicArray<T> getArr();
    private:
        void swap(T &a, T &b);
        void buildHeap(int parentIndex);
};

template <class T>
Heap<T>::Heap(){
    // queue = DynamicArray<T>();
    this->last = 0;
}

// template <typename T>
// Heap<T>::~Heap(){
//     delete queue;
// }

template <class T>
T Heap<T>::getFirst(){
   return queue.get(0);
}

template <class T>
void Heap<T>::push(T element)
{   
    // dodanie elementu na koniec kopca
    queue.add(element);
    last++;

    for (int i = last/2-1; i >= 0; i--) {
        buildHeap(i);
    }    
}

template <class T>
inline void Heap<T>::pop(){
    // zamiana korzenia z ostatnim dzieckiem
    swap(queue.get(0), queue.get(last-1));
    queue.removeAt(last-1);
    last--;
    // odbudowa kopca
    buildHeap(0);
}

template <class T>
inline int Heap<T>::getSize(){
    return last; 
}

template <class T>
inline DynamicArray<T> Heap<T>::getArr()
{
    return queue;
}

template <class T>
inline void Heap<T>::buildHeap(int parentIndex){
    int maxIndex = parentIndex;
    int leftChild = parentIndex * 2 + 1;
    int rightChild = parentIndex * 2 + 2;

    if (leftChild < last && queue.get(leftChild) < queue.get(maxIndex)) {
        maxIndex = leftChild;
    }
    if (rightChild < last && queue.get(rightChild) < queue.get(maxIndex)) {
        maxIndex = rightChild;
    }
    if (maxIndex != parentIndex) {
        swap(queue.get(maxIndex),queue.get(parentIndex));
        buildHeap(maxIndex);
    }
}

template <class T>
inline void Heap<T>::swap(T &a, T &b){
    auto temp = a;
    a = b;
    b = temp;
}


#endif