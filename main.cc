#include "grid.h"
#include "cell.h"
#include "observer.h"
#include "subject.h"
#include <iostream>

int main() {
    Grid g;
    g.init();
    std::cout << g;
}