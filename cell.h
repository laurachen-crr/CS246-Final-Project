#ifndef CELL_H
#define CELL_H
#include "piece.h"

class Cell {
    int r;
    int c;
    Piece * curPiece = nullptr;

public:
    Cell(int r, int c);
    void setPiece(Piece *mypiece); // Place a piece of given colour here.
};

#endif
