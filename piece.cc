#include "piece.h"

Piece::Piece(int row, int col, Colour colour, Type type) {
    this->pos = {row, col};
    this->colour = colour;
    this->type = type;
}

Colour Piece::getColour() {
    return this->colour;
}

Type Piece::getType() {
    return this->type;
}

King::King(int row, int col, Colour colour) : Piece{row, col, colour, Type::King} {}

Queen::Queen(int row, int col, Colour colour) : Piece{row, col, colour, Type::Queen} {}

Bishop::Bishop(int row, int col, Colour colour) : Piece{row, col, colour, Type::Bishop} {}

Pawn::Pawn(int row, int col, Colour colour) : Piece{row, col, colour, Type::Pawn} {}

Rook::Rook(int row, int col, Colour colour) :Piece::Piece{row, col, colour, Type::Rook} {}

Knight::Knight(int row, int col, Colour colour) : Piece{row, col, colour, Type::Knight} {}

bool King::checkValidMove(int r, int c) { 

}

bool Queen::checkValidMove(int r, int c) {

}

bool Bishop::checkValidMove(int r, int c) {

}

bool Pawn::checkValidMove(int r, int c) {

}

bool Rook::checkValidMove(int r, int c) {

}

bool Knight::checkValidMove(int r, int c) {

}

Pos King::findBestMove() {

}

Pos Queen::findBestMove() {
    
}

Pos Bishop::findBestMove() {
    
}

Pos Pawn::findBestMove() {
    
}

Pos Rook::findBestMove() {
    
}

Pos Knight::findBestMove() {
    
}


void Piece::MovePiece(int r, int c) {

}

void Piece::notify(Subject &whoFrom) {
    // downcast from subject to a grid (whoFrom MUST be class Grid) 
    Grid& grid = static_cast<Grid&>(whoFrom);
}