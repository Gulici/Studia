#ifndef UTILS
#define UTILS

#include <random>

int random(int begin, int end);

int random(int begin, int end) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(begin, end);

    return distribution(gen);
}

#endif