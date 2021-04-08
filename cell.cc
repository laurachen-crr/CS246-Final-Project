#include "cell.h"

Cell::Cell(int r, int c) {
    this->r = r;
    this->c = c;
}

void Cell::setPiece(Piece *mypiece) {
    this->curPiece = mypiece;
}

