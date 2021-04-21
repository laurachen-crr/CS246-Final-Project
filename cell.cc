#include "cell.h"
#include "enums.h"
#include "piece.h"

Cell::Cell(int r, int c) { this->pos = {r, c}; }

// set piece to cell
void Cell::setPiece(Piece* piece) {
    this->removePiece();
    if (piece != nullptr) {
        this->piece = piece;
        this->piece->setPos(this->pos.row, this->pos.col);
    }
}

// set cell piece to nullptr
void Cell::removePiece() {
    if (this->piece != nullptr) {
        this->piece->setPos(-1, -1);
        this->piece = nullptr;
    }
}

Piece* Cell::getPiece() { return this->piece; }
