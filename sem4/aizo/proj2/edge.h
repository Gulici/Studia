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

inline bool Edge::operator>(Edge &other)
{   
    bool w = this->getWeight() == other.getWeight();
    
    if(w){
        bool w2 = this->getV1() == other.getV1();
        if(w2) return this->getV2() > other.getV2();
        else return this->getV1() > other.getV1();
    }
    
    else return this->getWeight() > other.getWeight();
}

inline bool Edge::operator<(Edge &other)
{
    bool w = this->getWeight() == other.getWeight();
    
    if(w){
        bool w2 = this->getV1() == other.getV1();
        if(w2) return this->getV2() < other.getV2();
        else return this->getV1() < other.getV1();
    }

    else return this->getWeight() < other.getWeight();
}

std::ostream& operator<<(std::ostream &out, Edge &edge) {
    out << '(';
    out << edge.getV1() << ", ";
    out << edge.getV2() << ", ";
    out << edge.getWeight(); 
    out << ')';
    return out;
}

#endif