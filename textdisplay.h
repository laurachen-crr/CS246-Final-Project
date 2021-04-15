#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>
#include "observer.h"
#include "subject.h"
using namespace std;
class Cell;

class TextDisplay : public Observer {
    std::vector<std::vector<char>> theDisplay;

public:
    TextDisplay();
    void notify(Subject &board) override;

    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
    ~TextDisplay();
};

#endif
