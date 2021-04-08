#include "grid.h"

Grid::Grid() {
    this->grid.resize(8);
    for(int i = 0; i < 8; ++i) {
        this->grid.at(i).resize(8);
    }
    
    this->blackpawn.resize(8);
    this->whitepawn.resize(8);
    this->black.resize(8);
    this->whitepawn.resize(8);
    for(int i = 0; i < 8; ++i) {
        Info curinfo = { 1, i, Type::Pawn, Colour::Black};
        this->blackpawn.emplace_back(Piece(curinfo));
        curinfo = {6, i, Type::Pawn, Colour::White};
        this->whitepawn.emplace_back(Piece(curinfo));
    }
    this->black.emplace_back(Piece({0, 0, Type::Rook, Colour::Black}));
    this->black.emplace_back(Piece({0, 1, Type::Knight, Colour::Black}));
    this->black.emplace_back(Piece({0, 2, Type::Bishop, Colour::Black}));
    this->black.emplace_back(Piece({0, 3, Type::King, Colour::Black}));
    this->black.emplace_back(Piece({0, 4, Type::Queen, Colour::Black}));
    this->black.emplace_back(Piece({0, 5, Type::Bishop, Colour::Black}));
    this->black.emplace_back(Piece({0, 6, Type::Knight, Colour::Black}));
    this->black.emplace_back(Piece({0, 7, Type::Rook, Colour::Black}));

    this->black.emplace_back(Piece({7, 0, Type::Rook, Colour::White}));
    this->black.emplace_back(Piece({7, 1, Type::Knight, Colour::White}));
    this->black.emplace_back(Piece({7, 2, Type::Bishop, Colour::White}));
    this->black.emplace_back(Piece({7, 3, Type::King, Colour::White}));
    this->black.emplace_back(Piece({7, 4, Type::Queen, Colour::White}));
    this->black.emplace_back(Piece({7, 5, Type::Bishop, Colour::White}));
    this->black.emplace_back(Piece({7, 6, Type::Knight, Colour::White}));
    this->black.emplace_back(Piece({7, 7, Type::Rook, Colour::White}));
}


void Grid::init() {
    for(int i = 0; i < 8; ++i) {
        for(int j = 0; j < 8; ++j) {
            this->grid.at(i).emplace_back(Cell(i, j));
        }
    }

    // init all the pieces
    for(int i = 0; i < 8; ++i) {
        this->grid.at(0).at(i).setPiece(&this->black.at(i));
        this->grid.at(1).at(i).setPiece(&this->blackpawn.at(i));
        this->grid.at(6).at(i).setPiece(&this->white.at(i));
        this->grid.at(7).at(i).setPiece(&this->whitepawn.at(i));
    }

    for(int i = 0; i < 8; ++i) {
        this->grid.attach(&this->blackpawn.at(i));
        this->grid.attach(&this->black.at(i));
    }
}

