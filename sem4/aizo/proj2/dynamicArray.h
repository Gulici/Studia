#ifndef ARR
#define ARR
#include <iostream>
#include <memory>
#include <assert.h>

template<class T>
class DynamicArray {
    T *data;
    const int MIN_CAPACITY = 64;
    int CURRENT_CAPACITY = MIN_CAPACITY;
    int size;

    public:        
        DynamicArray();
        int getSize() const;  

        T& get(const int pos);

        void add(T element);

        void insert(T element, const int pos);

        void remove(const int pos);
        
    private:
        void resize();
        void copy(T temp[]);
};

template<class T>
DynamicArray<T>::DynamicArray() {
    data = new T[MIN_CAPACITY];
    size = 0;
}

template<class T> int DynamicArray<T>::getSize() const {
    return this->size;
}

template<class T> T& DynamicArray<T>::get(const int pos){
    // assert(pos < size && pos >= 0);
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
    assert(pos <= size && pos >= 0);

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

#endif