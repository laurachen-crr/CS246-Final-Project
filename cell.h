#ifndef CELL_H
#define CELL_H
#include "piece.h"

class Cell {
    int r;
    int c;
    Piece* curPiece = nullptr;

public:
    Cell(int r, int c);
    void setPiece(Piece *mypiece); // set mypiece on the cell
    void removePiece(); // remove the current piece
};

#endif
