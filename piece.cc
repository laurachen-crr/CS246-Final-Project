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

Pos Piece::getPos() {
    return this->pos;
}

King::King(int row, int col, Colour colour) : Piece{row, col, colour, Type::King} {}

Queen::Queen(int row, int col, Colour colour) : Piece{row, col, colour, Type::Queen} {}

Bishop::Bishop(int row, int col, Colour colour) : Piece{row, col, colour, Type::Bishop} {}

Pawn::Pawn(int row, int col, Colour colour) : Piece{row, col, colour, Type::Pawn} {}

Rook::Rook(int row, int col, Colour colour) :Piece::Piece{row, col, colour, Type::Rook} {}

Knight::Knight(int row, int col, Colour colour) : Piece{row, col, colour, Type::Knight} {}

bool King::checkValidMove(int r, int c) { 
    int rowdiff = this->getPos().row - r;
    int coldiff = this->getPos().col - c;
    if(rowdiff == 0 && coldiff == 0) {
        return false;
    } else if(rowdiff >= -1 && rowdiff <=1 && coldiff >= -1 && coldiff <=1) {
        return true;
    } else {
        return false;
    }
}

bool Queen::checkValidMove(int r, int c) {
    int rowdiff = this->getPos().row - r;
    int coldiff = this->getPos().col - c;
    if(rowdiff == 0 && coldiff == 0) {
        return false;
    }
    if(rowdiff == 0 || coldiff) {
        return true;
    } else if(abs(rowdiff) == abs(coldiff)) {
        return true;
    } else {
        return false;
    }
}

bool Bishop::checkValidMove(int r, int c) {
    int rowdiff = this->getPos().row - r;
    int coldiff = this->getPos().col - c;
    if(rowdiff == 0 && coldiff == 0) {
        return false;
    }
    if(abs(rowdiff) == abs(coldiff)) {
        return true;
    } else {
        return false;
    }
}

bool Pawn::checkValidMove(int r, int c) {
    
}

bool Rook::checkValidMove(int r, int c) {
    int rowdiff = this->getPos().row - r;
    int coldiff = this->getPos().col - c;
    if(rowdiff == 0 && coldiff == 0) {
        return false;
    } else if(rowdiff == 0 || coldiff == 0) {
        return true;
    } else {
        return false;
    }
}

bool Knight::checkValidMove(int r, int c) {
    int oldR = this->getPos().row;
    int oldC = this->getPos().col;

    if (r == oldR + 1 || r == oldR - 1) {
        if (c == oldC + 2 || c == oldC - 2) {
            return true;
        } else {
            return false;
        }
    } else if (r == oldR + 2 || r == oldR - 2) {
        if (c == oldC + 1 || c == oldC - 1) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
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