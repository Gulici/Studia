#ifndef EDGE
#define EDGE

#include <iostream>

class Edge{
    int _v1;
    int _v2;
    int _weight;
    public: 
        Edge();
        Edge(int v1, int v2, int weight);            
        int &getV1();
        int &getV2();
        int &getWeight();
        void print();
        bool operator>(Edge &other);
        bool operator<(Edge &other);
};

Edge::Edge(int v1, int v2, int weight) {
    this->_v1=v1;
    this->_v2=v2;
    this->_weight=weight;
}
Edge::Edge() {
}

int& Edge::getV1(){
    return _v1;
}

int& Edge::getV2(){
    return _v2;
}

int& Edge::getWeight(){
    return _weight;
}

inline void Edge::print(){
    std::cout << "(" << _v1 <<","<<_v2<<","<<_weight<<")"<<std::endl; 
}

inline bool Edge::operator>(Edge &other)
{   
    return this->getWeight() > other.getWeight();
}

inline bool Edge::operator<(Edge &other)
{
    return this->getWeight() < other.getWeight();
}

std::ostream& operator<<(std::ostream &out, Edge &edge) {
    out << edge.getV1() << ' ';
    out << edge.getV2() << ' ';
    out << edge.getWeight(); 
    return out;
}

#endif