#include "cell.h"
#include "enums.h"
#include "piece.h"

Cell::Cell(int r, int c) {
    this->r = r;
    this->c = c;
}

void Cell::setPiece(Piece *piece) { this->piece = piece; }

Piece* Cell::getPiece() {
    return this->piece;
}
