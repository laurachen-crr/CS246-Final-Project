#ifndef GRID_H
#define GRID_H
#include <iostream>
#include <vector>
#include "piece.h"
#include "cell.h"
#include "subject.h"
#include "textdisplay.h"

enum class Result { WhiteWin, BlackWin, Draw };
class TextDisplay;
class InvalidMove {};

class Grid : public Subject, public Observer {
    std::vector<std::vector<Cell>> grid; 
    std::vector<Piece *> black;
    std::vector<Piece *> white;

    TextDisplay td; // The text display.
    // GraphDisplay *gd = nullptr; // Another observer (intent:  graphics)
    void setObserver(Observer *ob);

public:
    Grid();
    ~Grid();
    void init();
    void move(char pieceName, int r, int c); // move pieceName to r, c
    bool check(); // check whether one side is checked
    Result checkmate(); // check whether the game is over
    void notify(Subject& lastMove) override;
    friend std::ostream &operator<<(std::ostream &out, const Grid &g);
};

#endif
