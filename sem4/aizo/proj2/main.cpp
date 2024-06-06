#include <iostream>
#include <chrono>
#include <string>
#include "dynamicArray.h"
#include "heap.h"
#include "graph.h"
#include "edge.h"
#include "prim.h"
#include "kruskal.h"
#include "dijkstra.h"
#include "fordbell.h"

using namespace std;

void menuMST(Graph g);
void menuSP(Graph g);

void menuTest() {
    char wybor = 'a';
    int graphSize = 5;
    int density = 100;

    while(wybor != '0') {
        cout << "Wybor typu problemu:\n1>Wyznaczanie MST 2>Wyznaczanie najkrotszej sciezki\n";
        cin.clear();
        cin >> wybor;
        switch (wybor)
        {
        // MST
        case '1': {
            char wybor2 = 'a';
            bool isDirected = false;
            while(wybor2 != '0') {
                cout << "\n1>Wygeneruj losowy graf\n2>Wczytaj graf z pliku\n";
                cin.clear();
                cin >> wybor2;
                switch(wybor2) {
                    // LOSOWY
                    case '1': {
                        char wybor3 = 'a';
                        while (wybor3 != '0')
                        {
                            cout << "\nObecnie wybrane wlasciwosci: rozmiar " << graphSize <<", gestosc "<< density <<'\n';
                            cout << "1>Wprowadzanie wlasciwosci\n2>Generuj graf\n";
                            cin.clear();
                            cin >> wybor3;

                            switch (wybor3)
                            {
                            case '1': {
                                cout << "Podaj ilosc wierzcholkow: ";
                                int temp;
                                cin.clear();
                                cin >> temp;
                                if(graphSize < 1 || graphSize > 1000) {
                                    cout << "\nPodano nieprawidlowa wartosc\n";
                                    break;
                                }
                                graphSize = temp;
                                cout << "Podaj gestosc: ";
                                cin.clear();
                                cin >> temp;
                                if(graphSize < 5 || graphSize > 100) {
                                    cout << "\nPodano nieprawidlowa wartosc\n";
                                    break;
                                }
                                density = temp;
                                break;
                            }
                            
                            case '2': {
                                Graph g = Graph(graphSize, density, isDirected);
                                menuMST(g);
                                break;
                            }

                            default: {
                                break;
                            }
                            }
                        }
                        break;
                    }
                    // WCZYTANY
                    case '2': {
                        cout << "Podaj nazwe pliku txt: ";
                        string filename;
                        cin >> filename;
                        DynamicArray<DynamicArray<int>> data = readFromTxt(filename);
                        if(data.getSize()>0) {
                            Graph g = Graph(data,isDirected);
                            menuMST(g);
                        }
                        break;
                    }
                    default: {
                        break;
                    }

                }
            }
            break;
        }

        // SP
        case '2': {
            char wybor2 = 'a';
            bool isDirected = true;
            while(wybor2 != '0') {
                cout << "\n1>Wygeneruj losowy graf\n2>Wczytaj graf z pliku\n";
                cin.clear();
                cin >> wybor2;
                switch(wybor2) {
                    // LOSOWY
                    case '1': {
                        char wybor3 = 'a';
                        while (wybor3 != '0')
                        {
                            cout << "\nObecnie wybrane wlasciwosci: rozmiar " << graphSize <<", gestosc "<< density <<'\n';
                            cout << "1>Wprowadzanie wlasciwosci\n2>Generuj graf\n";
                            cin.clear();
                            cin >> wybor3;

                            switch (wybor3)
                            {
                            case '1': {
                                cout << "Podaj ilosc wierzcholkow: ";
                                int temp;
                                cin.clear();
                                cin >> temp;
                                if(graphSize < 1 || graphSize > 1000) {
                                    cout << "\nPodano nieprawidlowa wartosc\n";
                                    break;
                                }
                                graphSize = temp;
                                cout << "Podaj gestosc: ";
                                cin.clear();
                                cin >> temp;
                                if(graphSize < 5 || graphSize > 100) {
                                    cout << "\nPodano nieprawidlowa wartosc\n";
                                    break;
                                }
                                density = temp;
                                break;
                            }
                            
                            case '2': {
                                Graph g = Graph(graphSize, density, isDirected);
                                menuSP(g);
                                break;
                            }

                            default: {
                                break;
                            }
                            }
                        }
                        break;
                    }
                    // WCZYTANY
                    case '2': {
                        cout << "Podaj nazwe pliku txt: ";
                        string filename;
                        cin >> filename;
                        DynamicArray<DynamicArray<int>> data = readFromTxt(filename);
                        if(data.getSize()>0) {
                            Graph g = Graph(data,isDirected);
                            menuSP(g);
                        }
                        break;
                    }
                    default: {
                        break;
                    }

                }
            }
            break;
        }

        default:
            break;
        }
    }
}

void menuMST(Graph g) {
    DynamicArray<DynamicArray<int>> &list = g.neighList();
    DynamicArray<DynamicArray<int>> &matrix = g.incidenceMatrix();

    char wybor = 'a';
    while(wybor != '0') {
    cout << "1>Wypisz liste sasiedztwa\n2>Wypisz macierz incydencji\n3>Wyznacz MST\n";
    cin.clear();
    cin >> wybor;

        switch (wybor)
        {
        case '1': {
            cout <<'\n';
            for(int i = 0; i < list.getSize(); i++) {
                DynamicArray<int> row = list.get(i);
                for(int j = 0; j < row.getSize(); j++) {
                    cout << row.get(j) << ' ';
                }
                cout<< '\n';
            }
            cout<<'\n';
            break;
        }

        case '2': {
            cout <<'\n';
            for(int i = 0; i < matrix.getSize(); i++) {
                DynamicArray<int> row = matrix.get(i);
                for(int j = 0; j < row.getSize(); j++) {
                    cout << row.get(j) << '\t';
                }
                cout<< '\n';
            }
            cout<<'\n';
            break;
        }

        case '3': {
            auto start = std::chrono::high_resolution_clock::now();
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> diff = end - start;
            auto tms = std::chrono::duration_cast<std::chrono::milliseconds>(diff);


            cout << "\nPRIM LISTA:\n"; 
            Prim p;
            start = std::chrono::high_resolution_clock::now();
            p.mstList(list);
            end = std::chrono::high_resolution_clock::now();
            diff = end - start;
            tms = std::chrono::duration_cast<std::chrono::milliseconds>(diff);
            p.print();
            std::cout << "Czas: " << tms.count() << std::endl;

            cout << "\nPRIM MACIERZ:\n";
            Prim pM;
            start = std::chrono::high_resolution_clock::now();
            pM.mstMatrix(matrix);
            end = std::chrono::high_resolution_clock::now();
            diff = end - start;
            tms = std::chrono::duration_cast<std::chrono::milliseconds>(diff);
            pM.print();
            std::cout << "Czas: " << tms.count() << std::endl;

            cout << "\nKRUSKAL LISTA:\n";
            Kruskal k;
            start = std::chrono::high_resolution_clock::now();
            k.mstList(list);
            end = std::chrono::high_resolution_clock::now();
            diff = end-start;
            tms = std::chrono::duration_cast<std::chrono::milliseconds>(diff);
            k.print();
            std::cout << "Czas: " << tms.count() << std::endl;

            cout << "\nKRUSKAL MACIERZ:\n";
            Kruskal k2;
            start = std::chrono::high_resolution_clock::now();
            k2.mstMatrix(matrix);
            end = std::chrono::high_resolution_clock::now();
            diff = end-start;
            tms = std::chrono::duration_cast<std::chrono::milliseconds>(diff);
            k2.print();
            std::cout << "Czas: " << tms.count() << std::endl;

            cout<< '\n';
        }
        
        default:
            break;
        }
    }
}

void menuSP(Graph g) {
    DynamicArray<DynamicArray<int>> &list = g.neighList();
    DynamicArray<DynamicArray<int>> &matrix = g.incidenceMatrix();
    int nV = list.getSize();

    char wybor = 'a';
    while(wybor != '0') {
    cout << "1>Wypisz liste sasiedztwa\n2>Wypisz macierz incydencji\n3>Wyznacz MST\n";
    cin.clear();
    cin >> wybor;

        switch (wybor)
        {
        case '1': {
            cout <<'\n';
            for(int i = 0; i < list.getSize(); i++) {
                DynamicArray<int> row = list.get(i);
                for(int j = 0; j < row.getSize(); j++) {
                    cout << row.get(j) << ' ';
                }
                cout<< '\n';
            }
            cout<<'\n';
            break;
        }

        case '2': {
            cout <<'\n';
            for(int i = 0; i < matrix.getSize(); i++) {
                DynamicArray<int> row = matrix.get(i);
                for(int j = 0; j < row.getSize(); j++) {
                    cout << row.get(j) << '\t';
                }
                cout<< '\n';
            }
            cout<<'\n';
            break;
        }

        case '3': {
            auto start = std::chrono::high_resolution_clock::now();
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> diff = end - start;
            auto tms = std::chrono::duration_cast<std::chrono::milliseconds>(diff);

            char wybor2 = 'a';
            while (wybor2 != '0')
            {
                cout << "1>Dijkstra dla listy\n2>Dijkstra dla macierzy\n3>Ford-Bellman dla listy\n4>Ford-Bellman dla macierzy\n";
                cin.clear();
                cin >> wybor2;

                switch (wybor2) {
                    case '1': {
                        cout << "\nDIJKSTRA LISTA:\n";
                        Dijkstra d;
                        start = std::chrono::high_resolution_clock::now();
                        d.spList(list);
                        end = std::chrono::high_resolution_clock::now();
                        diff = end-start;
                        tms = std::chrono::duration_cast<std::chrono::milliseconds>(diff);
                        std::cout << "Czas: " << tms.count() << std::endl;

                        char wybor3 = 'a';
                        while(wybor3 != '0') {
                            cout << "\n1>Podaj wierzcholek v2\n2>Wypisz drogi do wszytskich wierzcholkow\n";
                            cin.clear();
                            cin >> wybor3;

                            switch (wybor3) {
                                case '1': {
                                    int v2;
                                    cin.clear();
                                    cin >> v2;
                                    if(v2 < nV) d.getDistTo(v2);
                                    break;
                                }

                                case '2': {
                                    for(int i = 1; i < nV; i++) {
                                        d.getDistTo(i);
                                    }
                                }

                                default :{
                                    break;
                                }
                            }
                        }
                        break;
                    }
                    case '2': {
                        cout << "\nDIJKSTRA MACIERZ:\n";
                        Dijkstra d;
                        start = std::chrono::high_resolution_clock::now();
                        d.spMatrix(matrix);
                        end = std::chrono::high_resolution_clock::now();
                        diff = end-start;
                        tms = std::chrono::duration_cast<std::chrono::milliseconds>(diff);
                        std::cout << "Czas: " << tms.count() << std::endl;

                        char wybor3 = 'a';
                        while(wybor3 != '0') {
                            cout << "\n1>Podaj wierzcholek v2\n2>Wypisz drogi do wszytskich wierzcholkow\n";
                            cin.clear();
                            cin >> wybor3;

                            switch (wybor3) {
                                case '1': {
                                    int v2;
                                    cin.clear();
                                    cin >> v2;
                                    if(v2 < nV) d.getDistTo(v2);
                                    break;
                                }

                                case '2': {
                                    for(int i = 1; i < nV; i++) {
                                        d.getDistTo(i);
                                    }
                                }

                                default :{
                                    break;
                                }
                            }
                        }
                        break;
                    }
                    case '3': {
                        cout << "\nBELLMAN FORD LISTA:\n";
                        FordBell f;
                        start = std::chrono::high_resolution_clock::now();
                        f.spList(list);
                        end = std::chrono::high_resolution_clock::now();
                        diff = end-start;
                        tms = std::chrono::duration_cast<std::chrono::milliseconds>(diff);
                        std::cout << "Czas: " << tms.count() << std::endl;

                        char wybor3 = 'a';
                        while(wybor3 != '0') {
                            cout << "\n1>Podaj wierzcholek v2\n2>Wypisz drogi do wszytskich wierzcholkow\n";
                            cin.clear();
                            cin >> wybor3;

                            switch (wybor3) {
                                case '1': {
                                    int v2;
                                    cin.clear();
                                    cin >> v2;
                                    if(v2 < nV) f.getDistTo(v2);
                                    break;
                                }

                                case '2': {
                                    for(int i = 1; i < nV; i++) {
                                        f.getDistTo(i);
                                    }
                                }

                                default :{
                                    break;
                                }
                            }
                        }
                        break;
                    }
                    case '4': {
                        cout << "\nBELLMAN FORD MACIERZ:\n";
                        FordBell f;
                        start = std::chrono::high_resolution_clock::now();
                        f.spMatrix(matrix);
                        end = std::chrono::high_resolution_clock::now();
                        diff = end-start;
                        tms = std::chrono::duration_cast<std::chrono::milliseconds>(diff);
                        std::cout << "Czas: " << tms.count() << std::endl;

                        char wybor3 = 'a';
                        while(wybor3 != '0') {
                            cout << "\n1>Podaj wierzcholek v2\n2>Wypisz drogi do wszytskich wierzcholkow\n";
                            cin.clear();
                            cin >> wybor3;

                            switch (wybor3) {
                                case '1': {
                                    int v2;
                                    cin.clear();
                                    cin >> v2;
                                    if(v2 < nV) f.getDistTo(v2);
                                    break;
                                }

                                case '2': {
                                    for(int i = 1; i < nV; i++) {
                                        f.getDistTo(i);
                                    }
                                }

                                default :{
                                    break;
                                }
                            }
                        }
                        break;
                    }
                }
            }
            break;
        }
        
        default:
            break;
        }
    }
}

int main() {
    menuTest();   
    return 0;
}