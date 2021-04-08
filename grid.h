#ifndef GRID_H
#define GRID_H
#include <iostream>
#include <vector>
#include "piece.h"
#include "info.h"
#include "state.h"
#include "cell.h"
#include "subject.h"
#include "textdisplay.h"

class TextDisplay;
template <typename InfoType, typename StateType> class Observer;
class InvalidMove {};

class Grid : public Subject<Info, State>, public Observer<Info, State> {
    std::vector<std::vector<Cell>> grid; 
    std::vector<Piece> blackpawn;
    std::vector<Piece> whitepawn;
    std::vector<Piece> black;
    std::vector<Piece> white;

    TextDisplay *td = nullptr; // The text display.
    Observer<Info, State> *ob = nullptr; // Another observer (intent:  graphics)

public:
    Grid();
    ~Grid();
    void init();
    void setObserver(Observer<Info, State> *ob);
    // notify all the pieces on the grid
    void notify(Subject<Info, State> & lastMove) override;
};

#endif