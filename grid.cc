#include "grid.h"

Grid::Grid() {
    for(int i = 0; i < 8; ++i) {
        this->white.emplace_back(new Pawn({1, i, Colour::White}));
        this->black.emplace_back(new Pawn({6, i, Colour::Black}));
    }

    this->black.emplace_back(new Rook({7, 0, Colour::Black}));
    this->black.emplace_back(new Knight({7, 1, Colour::Black}));
    this->black.emplace_back(new Bishop({7, 2, Colour::Black}));
    this->black.emplace_back(new King({7, 3, Colour::Black}));
    this->black.emplace_back(new Queen({7, 4, Colour::Black}));
    this->black.emplace_back(new Bishop({7, 5, Colour::Black}));
    this->black.emplace_back(new Knight({7, 6, Colour::Black}));
    this->black.emplace_back(new Rook({7, 7, Colour::Black}));

    this->white.emplace_back(new Rook({0, 0, Colour::White}));
    this->white.emplace_back(new Knight({0, 1, Colour::White}));
    this->white.emplace_back(new Bishop({0, 2, Colour::White}));
    this->white.emplace_back(new King({0, 3, Colour::White}));
    this->white.emplace_back(new Queen({0, 4, Colour::White}));
    this->white.emplace_back(new Bishop({0, 5, Colour::White}));
    this->white.emplace_back(new Knight({0, 6, Colour::White}));
    this->white.emplace_back(new Rook({0, 7, Colour::White}));

    this->td = TextDisplay{};
}


void Grid::init() {
    for(int i = 0; i < 8; ++i) {
        this->grid.emplace_back(vector<Cell>{});
        for(int j = 0; j < 8; ++j) {
            this->grid.at(i).emplace_back(Cell{i, j});
        }
    }
    // init all the pieces
    for(int i = 0; i < 8; ++i) {
        this->grid.at(0).at(i).setPiece(this->black.at(i+8));
        this->grid.at(1).at(i).setPiece(this->black.at(i));
        this->grid.at(6).at(i).setPiece(this->white.at(i));
        this->grid.at(7).at(i).setPiece(this->white.at(i+8));
    }

    // attach observers(all pieces) to the grid
    for(int i = 0; i < 16; ++i) {
        this->attach(this->black.at(i));
        this->attach(this->black.at(i));
    }
    
    // attach grid to pieces as observer
    for(int i = 0; i < 16; ++i) {
        this->black.at(i)->attach(this);
        this->white.at(i)->attach(this);
    }
}

std::ostream &operator<<(std::ostream &out, const Grid &g) {
    out << g.td;
    return out;
}

void Grid::move(char pieceName, int r, int c) {

}

bool Grid::check() {

}

Result Grid::checkmate() {

}

void Grid::notify(Subject& lastMove) {

}

Grid::~Grid() {

}