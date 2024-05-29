#ifndef ARR
#define ARR
#include <iostream>
#include <ostream>
#include <memory>
#include <assert.h>
#include "edge.h"

template<class T>
class DynamicArray {
    T *data;
    const int MIN_CAPACITY = 8;
    int capacity = MIN_CAPACITY;
    int _size;

    public:        
        DynamicArray();
        ~DynamicArray();
        int getSize() const;  
        T& get(const int pos);
        void add(T& element);
        void insert(T& element, const int pos);
        void removeAt(const int pos);
        void remove(T element);
        DynamicArray<T>* getArray();
        inline void operator=(DynamicArray<T> &other);
        
    private:
        void resize();
};

template<class T>
DynamicArray<T>::DynamicArray() {
    this->data = new T[MIN_CAPACITY];
    _size = 0;
}

template <class T>
inline DynamicArray<T>::~DynamicArray(){
    delete[] data;
}

template<class T> int DynamicArray<T>::getSize() const {
    return this->_size;
}

template<class T> T& DynamicArray<T>::get(const int pos){
    assert(pos >= 0 && pos < _size);
    return data[pos];
}


template <class T>
void DynamicArray<T>::add(T &element)
{
    if(_size == capacity) {
        resize();
    }
    data[_size] = element;
    _size++;
}

template<class T> void DynamicArray<T>::insert(T& element, const int pos) {
    assert(pos >= 0 && pos < _size);

    if(_size == capacity) {
        resize();
    }

    _size++;

    for(int i = _size - 1; i >= pos; i--) {
        if(i == pos) {
            data[i] = element;
        } else {
            data[i] = data[i-1];
        }
    }
}

template<class T> void DynamicArray<T>::removeAt(const int pos) {
    assert(pos >= 0 && pos < _size);
    _size--;
    for(int i = pos; i < _size; i++) {
        data[i] = data[i+1];
    }
}



template <class T>
inline void DynamicArray<T>::remove(T element){
    //znajdz element
    for(int i = 0; i < _size; i++) {
        T temp = data[i];
        if(temp == element) {
            removeAt(i);
            return;
        }
    }
}

// funkcja zwracajaca wskaznik na nową dynamiczną tablice
template <class T>
inline DynamicArray<T>* DynamicArray<T>::getArray()
{   
    DynamicArray<T> *newA = new DynamicArray<T>;
    newA->capacity = this->capacity;
    newA->data = new T[newA->capacity];
    newA->_size = this->_size;
    std::copy(data, data + _size, newA->data);
    return newA; 
}


template <class T>
inline void DynamicArray<T>::operator=(DynamicArray<T> &other)
{   
    this->capacity = other.capacity;
    this->_size = other._size;
    std::copy(other.data, other.data + _size, data);
}

template<class T> void DynamicArray<T>::resize() {
    capacity *= 2;
    T *temp = new T[capacity];
    std::copy(data, data + _size, temp);
    delete [] data;
    data = temp;
}
#endif

