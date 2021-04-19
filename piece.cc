#include "piece.h"

#include "grid.h"
#include "utils.h"

Piece::Piece(int row, int col, Colour colour, Type type) {
    this->pos = {row, col};
    this->colour = colour;
    this->type = type;
}

// factory method pattern
// use this instead of Piece subclass constructors
Piece* Piece::createPiece(int row, int col, Colour colour, Type type) {
    switch (type) {
        case Type::Bishop:
            return new Bishop{row, col, colour};
        case Type::King:
            return new King{row, col, colour};
        case Type::Queen:
            return new Queen{row, col, colour};
        case Type::Knight:
            return new Knight{row, col, colour};
        case Type::Pawn:
            return new Pawn{row, col, colour};
        case Type::Rook:
            return new Rook{row, col, colour};
        default:
            return nullptr;
    }
}

Colour Piece::getColour() { return this->colour; }

Type Piece::getType() { return this->type; }

Pos Piece::getPos() { return this->pos; }

void Piece::setPos(int r, int c) { this->pos = {r, c}; }

King::King(int row, int col, Colour colour)
    : Piece{row, col, colour, Type::King} {}

Queen::Queen(int row, int col, Colour colour)
    : Piece{row, col, colour, Type::Queen} {}

Bishop::Bishop(int row, int col, Colour colour)
    : Piece{row, col, colour, Type::Bishop} {}

Pawn::Pawn(int row, int col, Colour colour)
    : Piece{row, col, colour, Type::Pawn} {}

Rook::Rook(int row, int col, Colour colour)
    : Piece::Piece{row, col, colour, Type::Rook} {}

Knight::Knight(int row, int col, Colour colour)
    : Piece{row, col, colour, Type::Knight} {}

bool King::checkValidMove(int r, int c, Grid& g) {  // need modification
}

bool Queen::checkValidMove(int r, int c, Grid& g) {  // need modification
}

bool Bishop::checkValidMove(int r, int c, Grid& g) {}

bool Pawn::checkValidMove(int r, int c, Grid& g) {}

bool Rook::checkValidMove(int r, int c, Grid& g) {}

bool Knight::checkValidMove(int r, int c, Grid& g) {}

vector<Pos> King::getValidMoves(Grid& g) {
    vector<Pos> allValidMoves;
    int row = this->getPos().row;
    int col = this->getPos().col;
    Colour colour = this->getColour();

    for (int r = -1; r <= 1; ++r) {
        for (int c = -1; c <= 1; ++c) {
            if (Utils::onBoard(r + row, c + col)) {
                Piece* piece = g.getPiece(r + row, c + col);
                if (piece == nullptr || piece->getColour() != colour) {
                    Pos pos = {r + row, c + col};
                    allValidMoves.emplace_back(pos);
                }
            }
        }
    }
    return allValidMoves;
}

vector<Pos> Queen::getValidMoves(Grid& g) {
    vector<Pos> allValidMoves;
    
}

vector<Pos> Bishop::getValidMoves(Grid& g) {}

vector<Pos> Pawn::getValidMoves(Grid& g) {
    int row = this->getPos().row;
    int col = this->getPos().col;
    vector<Pos> allValidMoves;

    if(this->getColour() == Colour::White) {
        if(row != 0) {
            if(g.getPiece(row-1, col) == nullptr) {
                allValidMoves.push_back({row-1, col});
            }

            if(Utils::onBoard(row-1, col+1)) {
                if(g.getPiece(row-1, col+1) != nullptr && g.getPiece(row-1, col+1)->getColour() == Colour::Black) {
                    allValidMoves.push_back({row-1, col+1});
                }
            } else if(Utils::onBoard(row-1, col-1)) {
                if(g.getPiece(row-1, col-1) != nullptr && g.getPiece(row-1, col-1)->getColour() == Colour::Black) {
                    allValidMoves.push_back({row-1, col-1});
                }
            }
            if(row == 6) {
                if(g.getPiece(4, col) == nullptr) {
                    allValidMoves.push_back({4, col});
                } 
            }
        }
    } else {
        if(row != 7) {
            if(g.getPiece(row+1, col) == nullptr) {
                allValidMoves.push_back({row+1, col});
            }
            
            if(Utils::onBoard(row+1, col+1)) {
                if(g.getPiece(row+1, col+1) != nullptr && g.getPiece(row+1, col+1)->getColour() == Colour::White) {
                    allValidMoves.push_back({row+1, col+1});
                }
            } else if(Utils::onBoard(row+1, col-1)) {
                if(g.getPiece(row+1, col-1) != nullptr && g.getPiece(row+1, col-1)->getColour() == Colour::White) {
                    allValidMoves.push_back({row+1, col-1});
                }
            }
            if(row == 1) {
                if(g.getPiece(3, col) == nullptr) {
                    allValidMoves.push_back({3, col});
                }
                
            }
        }
    }
    return allValidMoves;
}

vector<Pos> Knight::getValidMoves(Grid& g) {
    int row = this->getPos().row;
    int col = this->getPos().col;
    vector<Pos> allValidMoves;

    if(Utils::onBoard(row+2, col+1)) {
        allValidMoves.push_back({row+2, col+1});
        if(g.getPiece(row+2, col+1) != nullptr && g.getPiece(row+2, col+1)->getColour() == this->getColour()) {
            allValidMoves.pop_back();
        }
    } else if(Utils::onBoard(row-2, col+1)) {
        allValidMoves.push_back({row-2, col+1});
        if(g.getPiece(row-2, col+1) != nullptr && g.getPiece(row-2, col+1)->getColour() == this->getColour()) {
            allValidMoves.pop_back();
        }
    } else if(Utils::onBoard(row+2, col-1)) {
        allValidMoves.push_back({row+2, col-1});
        if(g.getPiece(row+2, col-1) != nullptr && g.getPiece(row+2, col-1)->getColour() == this->getColour()) {
            allValidMoves.pop_back();
        }
    } else if(Utils::onBoard(row-2, col-1)) {
        allValidMoves.push_back({row-2, col-1});
        if(g.getPiece(row-2, col-1) != nullptr && g.getPiece(row-2, col-1)->getColour() == this->getColour()) {
            allValidMoves.pop_back();
        }
    }
    return allValidMoves;
}

vector<Pos> Rook::getValidMoves(Grid& g) {}

Pos King::findBestMove() {}

Pos Queen::findBestMove() {}

Pos Bishop::findBestMove() {}

Pos Pawn::findBestMove() {}

Pos Rook::findBestMove() {}

Pos Knight::findBestMove() {}

void Piece::MovePiece(int r, int c) {
    this->pos.row = r;
    this->pos.col = c;
}

void Piece::notify(Subject& whoFrom) {
    // downcast from subject to a grid (whoFrom MUST be class Grid)
    Grid& grid = static_cast<Grid&>(whoFrom);
}
