#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <limits.h>
#include <chrono>

using namespace std;

vector<int> randomInts(int ilosc);
vector<int> ascInts(int ilosc);
vector<int> descInts(int ilosc);
vector<int> asc33Ints(int ilosc);
vector<int> asc66Ints(int ilosc);

vector<float> randomFloats(int ilosc);

template<typename T> void saveVecToTxt(const vector<T> &vec, const string &filename);
template<typename T> vector<T> readVecFromTxt(const string &filename, vector<T> &typeDed);
template<typename T> void printVector(const vector<T> &vec);
template<typename T> void swap(T* a, T* b);
template<typename T> bool isSorted(const vector<T> &vec);

template<typename T> vector<T> insertionSort(const vector<T> &vec);
template<typename T> vector<T> heapSort(const vector<T> &vec);
template<typename T> void buildHeap(vector<T> &vec, int heapSize, int parentIndex);
template<typename T> vector<T> shellSort(const vector<T> &vec);
template<typename T> vector<T> shellSort_Knuth(const vector<T> &vec);
template<typename T> vector<T> quickSortInit(const vector<T> &vec, int pivotType);
template<typename T> void quickSort(vector<T> &res,int l,int r, int pivotType);
template<typename T> vector<T> quickSortInitDesc(const vector<T> &vec);
template<typename T> void quickSortDesc(vector<T> &res,int l,int r);

void menuTest() {
    char wybor = 'a';
    char arrType = 'i';
    int arrSize = 10;
    int sortType = 1;
    int arrBefore = 0;
    vector<int> arrInt;
    vector<float> arrFloat;

    cout << "1>Wybor typu danych\n2>Wybor wielkosci tablicy\n3>Wybor wstepnego uporzadkowania tablicy\n";
    cout << "4>Wygeneruj tablice i zapisz do pliku\n5>Wczytaj tablice z pliku\n6>Sortuj\n";
    while(wybor != '0') {
        cin.clear();
        cin >> wybor;
        switch(wybor) {
            case '1': {
                cout << "1>int\n2>float\n";
                cin.clear();
                char typeChoose = 'a';
                cin >> typeChoose;
                if(typeChoose == '1') arrType = 'i';
                else if(typeChoose == '2') arrType = 'f';
                else {
                    cout << "Bledny wybor. Obecnie wybrane: " << arrType << endl;
                }
                break;
            }
            case '2': {
                cout << "Obecny rozmiar: " << arrSize << " Podaj wielkosc tablicy:\n";
                int temp = 0;
                cin.clear();
                cin >> temp;
                if (temp < 5) {
                    cout << "Bledny wybor lub za mala tablica - min rozmiar to 5\n";
                }
                else {
                    arrSize = temp;
                }
                break;
            }
            case '3': {
                string typ;
                cout << "Obecny typ generowanej tablicy: ";
                if(arrBefore == 0) typ = "losowa";
                else if(arrBefore == 1) typ = "niemalejaca";
                else if(arrBefore == 2) typ = "nierosnaca";
                else if(arrBefore == 3) typ = "1/3 od dolu posortowana";
                else if(arrBefore == 4) typ = "1/3 od gory posortowana";
                cout << typ << endl;

                cout << "0>losowa 1>niemalejaca 2>nierosnaca 3>1/3 od dolu posortowana 4>1/3 od gory posortowana\n";
                int temp = 0;
                cin.clear();
                cin >> temp;
                if(temp == 0) arrBefore = 0;
                else if(temp == 1) arrBefore = 1;
                else if(temp == 2) arrBefore = 2;
                else if(temp == 3) arrBefore = 3;
                else if(temp == 4) arrBefore = 4;
                else {
                    cout << "Nieprawidlowy wybor wstepnego sortowania\n";
                    break;
                }
                break;
            }
            case '4': {
                if(arrType == 'i') {
                    if(arrBefore == 0) arrInt = randomInts(arrSize);
                    else if(arrBefore == 1) arrInt = ascInts(arrSize);
                    else if(arrBefore == 2) arrInt = descInts(arrSize);
                    else if(arrBefore == 3) arrInt = asc33Ints(arrSize);
                    else if(arrBefore == 4) arrInt = asc66Ints(arrSize);
                    saveVecToTxt(arrInt,"beforeInts.txt");
                }
                else if(arrType == 'f') {
                    arrFloat = randomFloats(arrSize);
                    saveVecToTxt(arrFloat,"beforeFloats.txt");
                }
                break;
            }
            case '5': {
                if(arrType == 'i') {
                    string filename = "beforeInts.txt";
                    arrInt = readVecFromTxt(filename, arrInt);
                }
                else if(arrType == 'f') {
                    string filename = "beforeFloats.txt";
                    arrFloat = readVecFromTxt(filename, arrFloat);
                }
                break;
            }
            case '6': {
                int sortChoose = 0;
                cout << "Podaj typ sortowania:\n1>Insertion Sort 2>Heap Sort 3>ShellSort 4>ShellSort_Knuth 5>Quick Sort\n";
                cin.clear();
                cin >> sortChoose;

                switch(sortChoose) {
                    case 1:{
                        if(arrType == 'i') {
                            auto start = chrono::high_resolution_clock::now();
                            vector<int> sorted = insertionSort(arrInt);
                            auto end = chrono::high_resolution_clock::now();
                            chrono::duration<double> diff = end - start;
                            auto tms = chrono::duration_cast<chrono::milliseconds>(diff);
                            cout << "Czas: " << tms.count() << endl; 
                            if(isSorted(sorted)) {
                                saveVecToTxt(sorted,"afterIns.txt");
                            }
                            if(arrInt.size()<=30) {
                                cout << "Przed:\n";
                                printVector(arrInt);
                                cout << "Po:\n";
                                printVector(sorted);
                            }
                        }
                        else if(arrType == 'f') {
                            auto start = chrono::high_resolution_clock::now();
                            vector<float> sorted = insertionSort(arrFloat);
                            auto end = chrono::high_resolution_clock::now();
                            chrono::duration<double> diff = end - start;
                            auto tms = chrono::duration_cast<chrono::milliseconds>(diff); 
                            cout << "Czas: " << tms.count() << endl;
                            if(isSorted(sorted)) {
                                saveVecToTxt(sorted,"afterFloats.txt");
                            }
                            if(arrFloat.size()<=30) {
                                cout << "Przed:\n";
                                printVector(arrFloat);
                                cout << "Po:\n";
                                printVector(sorted);
                            }
                        }
                        break;
                    }
                    case 2:{
                        if(arrType == 'i') {
                            auto start = chrono::high_resolution_clock::now();
                            vector<int> sorted = heapSort(arrInt);
                            auto end = chrono::high_resolution_clock::now();
                            chrono::duration<double> diff = end - start;
                            auto tms = chrono::duration_cast<chrono::milliseconds>(diff);
                            cout << "Czas: " << tms.count() << endl; 
                            if(isSorted(sorted)) {
                                saveVecToTxt(sorted,"afterIns.txt");
                            }
                            if(arrInt.size()<=30) {
                                cout << "Przed:\n";
                                printVector(arrInt);
                                cout << "Po:\n";
                                printVector(sorted);
                            }
                        }
                        else if(arrType == 'f') {
                            auto start = chrono::high_resolution_clock::now();
                            vector<float> sorted = heapSort(arrFloat);
                            auto end = chrono::high_resolution_clock::now();
                            chrono::duration<double> diff = end - start;
                            auto tms = chrono::duration_cast<chrono::milliseconds>(diff); 
                            cout << "Czas: " << tms.count() << endl;
                            if(isSorted(sorted)) {
                                saveVecToTxt(sorted,"afterFloats.txt");
                            }
                            if(arrFloat.size()<=30) {
                                cout << "Przed:\n";
                                printVector(arrFloat);
                                cout << "Po:\n";
                                printVector(sorted);
                            }
                        }
                        break;
                    }
                    case 3:{
                        if(arrType == 'i') {
                            auto start = chrono::high_resolution_clock::now();
                            vector<int> sorted = shellSort(arrInt);
                            auto end = chrono::high_resolution_clock::now();
                            chrono::duration<double> diff = end - start;
                            auto tms = chrono::duration_cast<chrono::milliseconds>(diff);
                            cout << "Czas: " << tms.count() << endl; 
                            if(isSorted(sorted)) {
                                saveVecToTxt(sorted,"afterIns.txt");
                            }
                            if(arrInt.size()<=30) {
                                cout << "Przed:\n";
                                printVector(arrInt);
                                cout << "Po:\n";
                                printVector(sorted);
                            }
                        }
                        else if(arrType == 'f') {
                            auto start = chrono::high_resolution_clock::now();
                            vector<float> sorted = shellSort(arrFloat);
                            auto end = chrono::high_resolution_clock::now();
                            chrono::duration<double> diff = end - start;
                            auto tms = chrono::duration_cast<chrono::milliseconds>(diff); 
                            cout << "Czas: " << tms.count() << endl;
                            if(isSorted(sorted)) {
                                saveVecToTxt(sorted,"afterFloats.txt");
                            }
                            if(arrFloat.size()<=30) {
                                cout << "Przed:\n";
                                printVector(arrFloat);
                                cout << "Po:\n";
                                printVector(sorted);
                            }
                        }
                        break;
                    }
                    case 4:{
                        if(arrType == 'i') {
                            auto start = chrono::high_resolution_clock::now();
                            vector<int> sorted = shellSort_Knuth(arrInt); 
                            auto end = chrono::high_resolution_clock::now();
                            chrono::duration<double> diff = end - start;
                            auto tms = chrono::duration_cast<chrono::milliseconds>(diff);
                            cout << "Czas: " << tms.count() << endl;
                            if(isSorted(sorted)) {
                                saveVecToTxt(sorted,"afterIns.txt");
                            }
                            if(arrInt.size()<=30) {
                                cout << "Przed:\n";
                                printVector(arrInt);
                                cout << "Po:\n";
                                printVector(sorted);
                            }
                        }
                        else if(arrType == 'f') {
                            auto start = chrono::high_resolution_clock::now();
                            vector<float> sorted = shellSort_Knuth(arrFloat);
                            auto end = chrono::high_resolution_clock::now();
                            chrono::duration<double> diff = end - start;
                            auto tms = chrono::duration_cast<chrono::milliseconds>(diff); 
                            cout << "Czas: " << tms.count() << endl;
                            if(isSorted(sorted)) {
                                saveVecToTxt(sorted,"afterFloats.txt");
                            }
                            if(arrFloat.size()<=30) {
                                cout << "Przed:\n";
                                printVector(arrFloat);
                                cout << "Po:\n";
                                printVector(sorted);
                            }
                        }
                        break;
                    }
                    case 5:{
                        cout << "Podaj typ pivota\n1>Srodkowy 2>Skrajny lewy 3> Skrajny prawy 4> Losowy\n";
                        cin.clear();
                        int temp, pivotType;
                        cin >> temp;
                        if(temp == 1) pivotType = 0;
                        else if(temp == 2) pivotType = 1;
                        else if(temp == 3) pivotType = 2;
                        else if(temp == 4) pivotType = 3;
                        else {
                            cout << "Nieprawidlowy wybor pivota\n";
                            break;
                        }

                        if(arrType == 'i') {
                            auto start = chrono::high_resolution_clock::now();
                            vector<int> sorted = quickSortInit(arrInt, pivotType); 
                            auto end = chrono::high_resolution_clock::now();
                            chrono::duration<double> diff = end - start;
                            auto tms = chrono::duration_cast<chrono::milliseconds>(diff);
                            cout << "Czas: " << tms.count() << endl;
                            if(isSorted(sorted)) {
                                saveVecToTxt(sorted,"afterIns.txt");
                            }
                            if(arrInt.size()<=30) {
                                cout << "Przed:\n";
                                printVector(arrInt);
                                cout << "Po:\n";
                                printVector(sorted);
                            }
                        }
                        else if(arrType == 'f') {
                            auto start = chrono::high_resolution_clock::now();
                            vector<float> sorted = quickSortInit(arrFloat, pivotType);
                            auto end = chrono::high_resolution_clock::now();
                            chrono::duration<double> diff = end - start;
                            auto tms = chrono::duration_cast<chrono::milliseconds>(diff); 
                            cout << "Czas: " << tms.count() << endl;
                            if(isSorted(sorted)) {
                                saveVecToTxt(sorted,"afterFloats.txt");
                            }
                            if(arrFloat.size()<=30) {
                                cout << "Przed:\n";
                                printVector(arrFloat);
                                cout << "Po:\n";
                                printVector(sorted);
                            }
                        }
                        break;
                    }
                    default: {
                        cout << "Bledny wybor\n";
                        break;
                    }
                }
                break;
            }
            case '0': break;   
            default: {
                cout << "Nie roznano wyboru.\n";
                break;
            }
        }
    }
}

void exam() {
    cout << "1>Insertion Sort 2>Heap Sort 3>Shell Sort 4>Shell-Knuth Sort 5>Quick Sort\n";
    cin.clear();
    int wybor = 0;
    int n = 100;
    int beforeType = 0;
    int dataType = 0;
    cin >> wybor;
    cout << "0>Losowe 1>Niemalejace 2>Nierosnace 3>1/3 posortowane 4>2/3 posortowane\n";
    cin.clear();
    cin >> beforeType;
    cout << "0>Int 1>Float\n";
    cin.clear();
    cin >> dataType;
    switch(wybor) {
        case 1: {
            int rozmiary[] = {2500,5000,10000,15000,20000,30000,40000};
            vector<int> avgTimes;
            for(int i = 0; i < 7; i++) {
                cout << "i:" << i;
                float sumTime = 0;
                for(int j = 0; j < n; j++) {
                    if(j%5==0) cout << " " << j;

                    vector<int> vecInt;
                    vector<float> vecFloat;
                    if(!dataType){
                        if(beforeType == 0) vecInt = randomInts(rozmiary[i]);
                        else if (beforeType == 1) vecInt = ascInts(rozmiary[i]);
                        else if (beforeType == 2) vecInt = descInts(rozmiary[i]);
                        else if (beforeType == 3) vecInt = asc33Ints(rozmiary[i]);
                        else if (beforeType == 4) vecInt = asc66Ints(rozmiary[i]);
                    }
                    else {
                        vecFloat = randomFloats(rozmiary[i]);
                    }

                    auto start = chrono::high_resolution_clock::now();
                    if(!dataType) vector<int> res = insertionSort(vecInt);
                    else vector<float> res = insertionSort(vecFloat);
                    auto end = chrono::high_resolution_clock::now();
                    chrono::duration<double> diff = end - start;
                    auto tms = chrono::duration_cast<chrono::milliseconds>(diff);
                    sumTime += tms.count();
                }
                cout << endl;
                float avg = sumTime/n;
                avgTimes.push_back(avg);
            }
            if(!dataType) saveVecToTxt(avgTimes,"srednie_insertion_int.txt");
            else saveVecToTxt(avgTimes,"srednie_insertion_float.txt");
            break;
        }
        case 2: {
            int rozmiary[] = {50000,100000,200000,400000,800000,1600000,2400000};
            vector<int> avgTimes;
            for(int i = 0; i < 7; i++) {
                cout << "i:" << i;
                float sumTime = 0;
                for(int j = 0; j < n; j++) {
                    if(j%5==0) cout << " " << j;

                    vector<int> vecInt;
                    vector<float> vecFloat;
                    if(!dataType){
                        if(beforeType == 0) vecInt = randomInts(rozmiary[i]);
                        else if (beforeType == 1) vecInt = ascInts(rozmiary[i]);
                        else if (beforeType == 2) vecInt = descInts(rozmiary[i]);
                        else if (beforeType == 3) vecInt = asc33Ints(rozmiary[i]);
                        else if (beforeType == 4) vecInt = asc66Ints(rozmiary[i]);
                    }
                    else {
                        vecFloat = randomFloats(rozmiary[i]);
                    }

                    auto start = chrono::high_resolution_clock::now();
                    if(!dataType) vector<int> res = heapSort(vecInt);
                    else vector<float> res = heapSort(vecFloat);
                    auto end = chrono::high_resolution_clock::now();
                    chrono::duration<double> diff = end - start;
                    auto tms = chrono::duration_cast<chrono::milliseconds>(diff);
                    sumTime += tms.count();
                }
                cout << endl;
                float avg = sumTime/n;
                avgTimes.push_back(avg);
            }
            if(!dataType) saveVecToTxt(avgTimes,"srednie_heap_int.txt");
            else saveVecToTxt(avgTimes,"srednie_heap_float.txt");
            break;
        }
        case 3: {
            int rozmiary[] = {50000,100000,200000,400000,800000,1600000,2400000};
            vector<int> avgTimes;
            for(int i = 0; i < 7; i++) {
                cout << "i:" << i;
                float sumTime = 0;
                for(int j = 0; j < n; j++) {
                    if(j%5==0) cout << " " << j;

                    vector<int> vecInt;
                    vector<float> vecFloat;
                    if(!dataType){
                        if(beforeType == 0) vecInt = randomInts(rozmiary[i]);
                        else if (beforeType == 1) vecInt = ascInts(rozmiary[i]);
                        else if (beforeType == 2) vecInt = descInts(rozmiary[i]);
                        else if (beforeType == 3) vecInt = asc33Ints(rozmiary[i]);
                        else if (beforeType == 4) vecInt = asc66Ints(rozmiary[i]);
                    }
                    else {
                        vecFloat = randomFloats(rozmiary[i]);
                    }

                    auto start = chrono::high_resolution_clock::now();
                    if(!dataType) vector<int> res = shellSort(vecInt);
                    else vector<float> res = shellSort(vecFloat);
                    auto end = chrono::high_resolution_clock::now();
                    chrono::duration<double> diff = end - start;
                    auto tms = chrono::duration_cast<chrono::milliseconds>(diff);
                    sumTime += tms.count();
                }
                cout << endl;
                float avg = sumTime/n;
                avgTimes.push_back(avg);
            }
            if(!dataType) saveVecToTxt(avgTimes,"srednie_shell_int.txt");
            else saveVecToTxt(avgTimes,"srednie_shell_float.txt");
            break;
        } 
        case 4: {
            int rozmiary[] = {50000,100000,200000,400000,800000,1600000,2400000};
            vector<int> avgTimes;
            for(int i = 0; i < 7; i++) {
                cout << "i:" << i;
                float sumTime = 0;
                for(int j = 0; j < n; j++) {
                    if(j%5==0) cout << " " << j;

                    vector<int> vecInt;
                    vector<float> vecFloat;
                    if(!dataType){
                        if(beforeType == 0) vecInt = randomInts(rozmiary[i]);
                        else if (beforeType == 1) vecInt = ascInts(rozmiary[i]);
                        else if (beforeType == 2) vecInt = descInts(rozmiary[i]);
                        else if (beforeType == 3) vecInt = asc33Ints(rozmiary[i]);
                        else if (beforeType == 4) vecInt = asc66Ints(rozmiary[i]);
                    }
                    else {
                        vecFloat = randomFloats(rozmiary[i]);
                    }

                    auto start = chrono::high_resolution_clock::now();
                    if(!dataType) vector<int> res = shellSort_Knuth(vecInt);
                    else vector<float> res = shellSort_Knuth(vecFloat);
                    auto end = chrono::high_resolution_clock::now();
                    chrono::duration<double> diff = end - start;
                    auto tms = chrono::duration_cast<chrono::milliseconds>(diff);
                    sumTime += tms.count();
                }
                cout << endl;
                float avg = sumTime/n;
                avgTimes.push_back(avg);
            }
            if(!dataType) saveVecToTxt(avgTimes,"srednie_shellKnuth_int.txt");
            else saveVecToTxt(avgTimes,"srednie_shellKnuth_float.txt");
            break;
        }
        case 5: {
            vector<int> rozmiary = {50000,100000,200000,400000,800000,1600000,2400000};
            if (beforeType != 0) rozmiary = {2000,5000,8000,12000,15000,18000,22000};
            int typeVec = 0;
            vector<int> avgTimes;
            for(typeVec = 0; typeVec < 4; typeVec++){
                for(int i = 0; i < 7; i++) {
                    cout << "i:" << i;
                    float sumTime = 0;
                    for(int j = 0; j < n; j++) {
                        if(j%5==0) cout << " " << j;

                        vector<int> vecInt;
                        vector<float> vecFloat;
                        if(!dataType){
                            if(beforeType == 0) vecInt = randomInts(rozmiary[i]);
                            else if (beforeType == 1) vecInt = ascInts(rozmiary[i]);
                            else if (beforeType == 2) vecInt = descInts(rozmiary[i]);
                            else if (beforeType == 3) vecInt = asc33Ints(rozmiary[i]);
                            else if (beforeType == 4) vecInt = asc66Ints(rozmiary[i]);
                        }
                        else {
                            vecFloat = randomFloats(rozmiary[i]);
                        }

                        auto start = chrono::high_resolution_clock::now();
                        if(!dataType) vector<int> res = quickSortInit(vecInt, typeVec);
                        else vector<float> res = quickSortInit(vecFloat, typeVec);
                        auto end = chrono::high_resolution_clock::now();
                        chrono::duration<double> diff = end - start;
                        auto tms = chrono::duration_cast<chrono::milliseconds>(diff);
                        sumTime += tms.count();
                    }
                    cout << endl;
                    float avg = sumTime/n;
                    avgTimes.push_back(avg);
                }
            }
            if(!dataType) saveVecToTxt(avgTimes,"srednie_quick_int.txt");
            else saveVecToTxt(avgTimes,"srednie_quick_float.txt");

            break;
        } 
    }
    return;
}

int main() {

    char wybor = 'a';
    cout << "MENU:\n1>Test\n2>Badanie\n";
    while(wybor != '0') {
        cin >> wybor;
        switch(wybor) {
            case '1': {
                menuTest();
                break;
            }
            case '2': {
                exam();
                break;
            }
            case '0': break;   
            default: {
                cout << "Nie roznano wyboru.\n";
                break;
            }
        }
    }

    return 0;
}


vector<int> randomInts(int ilosc) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(INT_MIN, INT_MAX);

    vector<int> result;

    for (int i = 0; i < ilosc; ++i) {
        result.push_back(distribution(gen));
    }

    return result;
}

vector<int> ascInts(int ilosc) {
    vector<int> random = randomInts(ilosc);
    return quickSortInit(random,0);
}

vector<int> descInts(int ilosc) {
    vector<int> random = randomInts(ilosc);
    return quickSortInitDesc(random);
}

vector<int> asc33Ints(int ilosc) {
    vector<int> result;
    int n = ilosc /3;
    for(int i = 0; i < n; i++) {
        result.push_back(i);
    }
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> distribution(n, INT_MAX);

    for (int i = 0; i < ilosc-n; ++i) {
        result.push_back(distribution(gen));
    }

    return result;
}

vector<int> asc66Ints(int ilosc) {
    vector<int> result;
    int n = (ilosc/3)*2;
    for(int i = 0; i < n; i++) {
        result.push_back(i);
    }
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> distribution(n, INT_MAX);

    for (int i = 0; i < ilosc-n; ++i) {
        result.push_back(distribution(gen));
    }

    return result;
}

vector<float> randomFloats(int ilosc) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> distribution(INT_MIN, INT_MAX);

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

template<typename T> vector<T> readVecFromTxt(const string &filename, vector<T> &typeDed) {
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
    cout << "Wczytano tablice z pliku " << filename << endl;
    return vec;
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
bool isSorted(const vector<T> &vec){
    bool isSorted = true;
    unsigned long size = vec.size();

    for(long i = 0; i < size-1; i++) {
        if(vec[i] > vec[i+1]) {
            printf("Tablica nieposortowana\n");
            isSorted = false;
            return isSorted;
        }
    }
    printf("Tablica posortowana niemalejąco\n");
    return isSorted;
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

    //budowanie maksymalnego kopca - wywolanie funkcji porzadkujacej od ostatniego rodzica do korzenia
    for (int i = len/2-1; i >= 0; i--) {
        buildHeap(res, len, i);
    }

    //sortowanie właściwe - zamiana korzenia z ostatnim dzieckiem, 
    //następnie odbudowa kopca zaczynajac od korzenia
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

template <typename T>
vector<T> shellSort(const vector<T> &vec) {
    vector<T> res = vec;
    int len = res.size();

    for (int gap = len/2; gap > 0; gap /= 2) {
        for (int i = gap; i < len; i++) {
            auto temp = res[i];
            int j;
            for (j = i; j >= gap && res[j-gap] > temp; j-=gap) 
                res[j] = res[j-gap];
            res[j] = temp;
        }
    }
    return res;
}

template <typename T>
vector<T> shellSort_Knuth(const vector<T> &vec) {
    vector<T> res = vec;
    int len = res.size();

    //obliczenie gap
    int gap;
    for (gap = 1; gap < len; gap = 3*gap+1);
    gap /= 9;
    if (gap == 0) gap++;

    for (gap; gap > 0; gap /= 3) {
        for (int j = len - gap - 1; j >=0; j--) {
            auto temp = res[j];
            int i = j+gap;
            while (i<len && temp > res[i]) {
                res[i-gap] = res[i];
                i += gap;
            }
            res[i-gap] = temp;
        }
    }

    return res;
}

template <typename T>
vector<T> quickSortInit(const vector<T> &vec, int pivotType) {
    vector<T> res = vec;
    int len = res.size();

    int l = 0; 
    int r = len - 1;

    quickSort(res, l, r, pivotType);
    return res;
}

template <typename T>
void quickSort(vector<T> &res,int l,int r, int pivotType) {
    int i,j;

    if(pivotType == 0) i = (l+r)/2;
    else if(pivotType == 1) i = l;
    else if(pivotType == 2) i = r;
    else if(pivotType == 3) i = rand() % (r-l) + l;
    
    auto pivot = res[i];
    res[i] = res[r];

    for(i = j = l; i < r; i++) {
        if(res[i] < pivot) {
            swap(res[i], res[j]);
            j++;
        }
    }

    res[r] = res[j];
    res[j] = pivot;

    if(l < j - 1) quickSort(res, l, j - 1, pivotType);
    if(j + 1 < r) quickSort(res, j + 1, r, pivotType);
}

template <typename T>
vector<T> quickSortInitDesc(const vector<T> &vec) {
    vector<T> res = vec;
    int len = res.size();

    int l = 0; 
    int r = len - 1;

    quickSortDesc(res, l, r);
    return res;
}

template <typename T>
void quickSortDesc(vector<T> &res,int l,int r) {
    int i,j;
    i = (l+r)/2;
    
    auto pivot = res[i];
    res[i] = res[r];

    for(i = j = l; i < r; i++) {
        if(res[i] > pivot) {
            swap(res[i], res[j]);
            j++;
        }
    }

    res[r] = res[j];
    res[j] = pivot;

    if(l < j - 1) quickSortDesc(res, l, j - 1);
    if(j + 1 < r) quickSortDesc(res, j + 1, r);
}

