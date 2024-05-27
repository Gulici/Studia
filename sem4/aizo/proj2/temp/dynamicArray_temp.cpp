#include <iostream>
#include <memory>
#include <assert.h>

template<typename T>
class DynamicArray {
    T *data;
    const int MIN_CAPACITY = 64;
    int CURRENT_CAPACITY = MIN_CAPACITY;
    int size;

    public:        
        DynamicArray() {
            data = new T[MIN_CAPACITY];
            size = 0;
        }

        int getSize() const {
            return size;
        }

        T& get(const int pos) const {
            assert(pos < size && pos >= 0);
            return data[pos];
        }

        void add(T element) {
            if(size == CURRENT_CAPACITY) {
                resize();
            }
            data[size]=element;
            size++;
        }

        void insert(T element, const int pos) {
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

        void remove(const int pos) {
            assert(pos < size && pos >= 0);

            for(int i = pos; i < size - 1; i++) {
                data[i] = data[i+1];
            }

            size--;
        }
        
    private:
        void resize() {
            CURRENT_CAPACITY *= 2;
            T *temp = new T[CURRENT_CAPACITY];
            copy(temp);
            delete [] data;
            data = temp;
        }

        void copy(T temp[]) {
            for(int i = 0; i < size; i++) {
                temp[i] = data[i];
            }
        }
};


int main() {
    DynamicArray<int> arr;
    DynamicArray<int> arr2;
    for(int i = 0; i < 150; i ++) {
        arr.add(i);
        arr2.add(i);
    }

    arr.remove(1);
    arr.get(1) = 50;

    for(int i = 0; i < arr2.getSize(); i++) {
        std::cout << arr2.get(i) << std::endl;
    }

    return 0;
}