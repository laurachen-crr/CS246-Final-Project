#ifndef COMPUTER_H
#define COMPUTER_H
#include <utility>
#include "structs.h"
#include "enums.h"
using namespace std;

class Grid;

class Computer {
    public:
    virtual pair<Pos, Pos> getNextMove(Grid& g, Colour colour) = 0;
    virtual ~Computer() = 0;
    static Computer* createComputer(int level);
};

class Computer1 : public Computer {
    public:
    pair<Pos, Pos> getNextMove(Grid& g, Colour colour) override;
    ~Computer1();
};

class Computer2 : public Computer {
    public:
    pair<Pos, Pos> getNextMove(Grid& g, Colour colour) override;
    ~Computer2();
};

class Computer3 : public Computer {
    public:
    pair<Pos, Pos> getNextMove(Grid& g, Colour colour) override;
    ~Computer3();
};

#endif
