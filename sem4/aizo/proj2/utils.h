#ifndef UTILS
#define UTILS

#include <random>
#include <string>
#include <iostream>
#include <fstream>
#include "dynamicArray.h"

int random(int begin, int end);
DynamicArray<DynamicArray<int>> readFromTxt(const std::string &filename);

int random(int begin, int end) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(begin, end);

    return distribution(gen);
}

inline DynamicArray<DynamicArray<int>> readFromTxt(const std::string &filename) {
    DynamicArray<DynamicArray<int>> arr;
    std::ifstream file(filename);

    if(file.is_open()) {
        int number;

        //naglowek
        DynamicArray<int> row;
        for(int i = 0; i < 2; i++) {
            file >> number;
            row.add(number);
        }
        arr.add(row);

        //wczytanie krawedzi
        int nE = row.get(0);
        for(int i = 0; i < nE; i++) {
            DynamicArray<int> row;
            int v1, v2, w;
            file >> v1 >> v2 >> w;
            row.add(v1);
            row.add(v2);
            row.add(w);
            arr.add(row);
        }

        file.close();
    }
    else {
        std::cerr << "Nie udało się otworzyć pliku do odczytu\n";
    }
    std::cout << "Wczytano tablice z pliku " << filename << '\n';
    return arr;
}

#endif