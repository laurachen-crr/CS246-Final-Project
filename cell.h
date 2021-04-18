#ifndef CELL_H
#define CELL_H
#include "structs.h"

class Piece;

class Cell {
    Pos pos;
    Piece* piece = nullptr;

public:
    Cell(int r, int c);
    void setPiece(Piece *piece); // set mypiece on the cell
    void removePiece(); // remove the current piece
    Piece* getPiece();
};

#endif
