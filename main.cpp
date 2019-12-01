#include <iostream>
#include "genetic.hpp"


int main() {
    auto g = genetic::getInstance();
    g->run();
    return 0;
}