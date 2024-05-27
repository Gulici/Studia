#include <iostream>
#include <assert.h>
#include <memory>
#include "dynamicArray.h"
#include "edge.h"

template<class T>
DynamicArray<T>::DynamicArray() {
    T data[MIN_CAPACITY];
    size = 0;
}

template<class T> int DynamicArray<T>::getSize() const {
    return this->size;
}

template<class T> T& DynamicArray<T>::get(const int pos){
    assert(pos < size && pos >= 0);
    return data[pos];
}

template<class T> void DynamicArray<T>::add(T element) {
    if(size == CURRENT_CAPACITY) {
        resize();
    }
    data[size]=element;
    size++;
}

template<class T> void DynamicArray<T>::insert(T element, const int pos) {
    assert(pos < size && pos >= 0);

    if(size == CURRENT_CAPACITY) {
        resize();
    }

    size++;

    for(int i = size - 1; i >= pos; i--) {
        if(i == pos) {
            data[i] = element;
        } else {
            data[i] = data[i-1];
        }
    }
}

template<class T> void DynamicArray<T>::remove(const int pos) {
    assert(pos < size && pos >= 0);

    for(int i = pos; i < size - 1; i++) {
        data[i] = data[i+1];
    }

    size--;
}


template<class T> void DynamicArray<T>::resize() {
    CURRENT_CAPACITY *= 2;
    T *temp = new T[CURRENT_CAPACITY];
    copy(temp);
    delete [] data;
    data = temp;
}

template<class T> void DynamicArray<T>::copy(T temp[]) {
    for(int i = 0; i < size; i++) {
        temp[i] = data[i];
    }
}

template class DynamicArray<int>;
template class DynamicArray<Edge>;
