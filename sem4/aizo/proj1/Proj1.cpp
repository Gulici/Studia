#include <iostream>
#include <fstream>
#include <random>
#include <vector>

using namespace std;

vector<int> randomInts(int ilosc, int min, int max);
vector<float> randomFloats(int ilosc, int min, int max);
template<typename T> void saveVecToTxt(const vector<T> &vec, const string &filename);
template<typename T> vector<T> readVecFromTxt(const string &filename);
template<typename T> void printVector(const vector<T> &vec);
template<typename T> void swap(T* a, T* b);

template<typename T> vector<T> insertionSort(const vector<T> &vec);
template<typename T> vector<T> heapSort(const vector<T> &vec);
template<typename T> void buildHeap(vector<T> &vec, int heapSize, int parentIndex);

int main() {

    int ilosc = 10; 
    int min = 1;   
    int max = 20; 
    
    vector<float> vecInts = randomFloats(ilosc,min,max);
    vector<float> heap = heapSort(vecInts);
    printVector(vecInts);
    printVector(heap);
    // vector<int> resInts = insertionSort(vecInts);

    // vector<float> vecFloats = randomFloats(ilosc, min, max);
    // vector<float> resFloats = insertionSort(vecFloats);

    // printVector(vecInts);
    // printVector(resInts);
    // printVector(vecFloats);
    // printVector(resFloats);

    return 0;
}


vector<int> randomInts(int ilosc, int min, int max) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(min, max);

    vector<int> result;

    for (int i = 0; i < ilosc; ++i) {
        result.push_back(distribution(gen));
    }

    return result;
}

vector<float> randomFloats(int ilosc, int min, int max) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> distribution(min, max);

    vector<float> result;

    for (int i = 0; i < ilosc; ++i) {
        result.push_back(distribution(gen));
    }

    return result;
}

template <typename T> void saveVecToTxt(const vector<T> &vec, const string &filename) {
    ofstream file(filename);

    if(file.is_open()) {
        for (const auto& number : vec) {
            file << number << endl;
        }
        file.close();
        cout << "Zapisano do pliku: " << filename << endl;
    }
    else {
        cerr << "Nie udało się otworzyć pliku." << endl;
    }
}

template<typename T> vector<T> readVecFromTxt(const string &filename) {
    vector<T> vec;
    ifstream file(filename);

    if(file.is_open()) {
        T number;
        while (file >> number) {
            vec.push_back(number);
        }
        file.close();
    }
    else {
        cerr << "Nie udało się otworzyć pliku do odczytu" << endl;
    }
}

template <typename T>
void printVector(const vector<T> &vec)
{
    for(auto &num : vec) {
        cout << num << " ";
    }
    cout << endl;
}

template <typename T>
void swap(T *a, T *b)
{
    auto temp = *a;
    *a = *b;
    *b = temp;
}


template <typename T>
vector<T> insertionSort(const vector<T> &vec) {
    vector<T> res = vec;
    int len = res.size();

    for (int i = 1; i < len; i++) {
        auto key = res[i];
        int j = i-1;
    
        while (j >= 0 && res[j] > key) {
            swap(res[j], res[j+1]);
            j--;
        }
    }

    return res;
}

template <typename T>
vector<T> heapSort(const vector<T> &vec)
{
    vector<T> res = vec;
    int len = res.size();

    for (int i = len/2-1; i >= 0; i--) {
        buildHeap(res, len, i);
    }

    for (int i=len-1; i>0; i--) {
        swap(res[0], res[i]);
        len--;
        buildHeap(res,len,0);
    }

    return res;
}

template <typename T>
void buildHeap(vector<T> &vec, int heapSize, int parentIndex)
{
    int maxIndex = parentIndex;
    int leftChild = parentIndex * 2 + 1;
    int rightChild = parentIndex * 2 + 2;

    if (leftChild < heapSize && vec[leftChild] > vec[maxIndex]) {
        maxIndex = leftChild;
    }
    if (rightChild < heapSize && vec[rightChild] > vec[maxIndex]) {
        maxIndex = rightChild;
    }
    if (maxIndex != parentIndex) {
        swap(vec[maxIndex],vec[parentIndex]);
        buildHeap(vec, heapSize, maxIndex);
    }
}
