#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>
#include "observer.h"
#include "subject.h"
using namespace std;

class Cell;
class Grid;

class TextDisplay {
    std::vector<std::vector<char>> theDisplay;
    std::vector<std::vector<char>> emptyboard;

public:
    TextDisplay();
    void init();
    void update(Grid& g);
    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
    ~TextDisplay();
};

#endif
