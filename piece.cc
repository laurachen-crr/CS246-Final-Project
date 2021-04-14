#include "piece.h"

Piece::Piece(int row, int col, Colour colour, Type type) {
    this->pos = { row, col};
    this->colour = colour;
    this->type = type;
}

King::King(int row, int col, Colour colour) : Piece{row, col, colour, Type::King} {}

Queen::Queen(int row, int col, Colour colour) : Piece{row, col, colour, Type::Queen} {}

Bishop::Bishop(int row, int col, Colour colour) : Piece{row, col, colour, Type::Bishop} {}

Pawn::Pawn(int row, int col, Colour colour) : Piece{row, col, colour, Type::King} {}

Rook::Rook(int row, int col, Colour colour) :Piece::Piece{row, col, colour, Type::King} {}

Knight::Knight(int row, int col, Colour colour) : Piece{row, col, colour, Type::King} {}

