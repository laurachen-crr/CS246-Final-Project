#include "grid.h"
#include "textdisplay.h"
#include "utils.h"

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

    this->td = new TextDisplay{};
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
    // update textdisplay
    this->td->update(*this);

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

// gets piece at (r, c)
Piece* Grid::getPiece(int r, int c) {
    return this->grid.at(r).at(c).getPiece();
}

std::ostream &operator<<(std::ostream &out, const Grid &g) {
    out << *g.td;
    return out;
}

void Grid::move(Colour colour, int r, int c) {
    
}

bool Grid::check() {
    return false;
}

// sets newPiece at (r, c)
// this method does not clean up memory or validate!
bool Grid::setPiece(int r, int c, Piece* newPiece) {
    Piece* oldPiece = this->getPiece(r, c);
    this->removePiece(oldPiece);
    this->grid.at(r).at(c).setPiece(newPiece);
    if (newPiece != nullptr) {
        Colour colour = newPiece->getColour();
        if (colour == Colour::White) {
            this->white.emplace_back(newPiece);
        } else {
            this->black.emplace_back(newPiece);
        }
    }
}

// creates new piece at (r, c)
// return true if validation passes, else false
// this method cleans up memory and validates
bool Grid::setPiece(Colour colour, int r, int c, Type type) {
    Piece* oldPiece = this->getPiece(r, c);
    Piece* newPiece = Utils::createPiece(r, c, colour, type);
    this->setPiece(r, c, newPiece);
    if (this->check()) { // in check
        this->setPiece(r, c, oldPiece);
        delete newPiece;
        return false;
    } else if (type == Type::Pawn && (r == 0 || r == 7)) { // pawn on last/first row
        this->setPiece(r, c, oldPiece);
        delete newPiece;
        return false;
    } else if (type == Type::King && findPiece(type, colour) != nullptr) { // king already exists
        this->setPiece(r, c, oldPiece);
        delete newPiece;
        return false;
    } else {
        delete oldPiece;
        this->td->update(*this);
        return true;
    }
}

// return first found piece that match type and colour
Piece* Grid::findPiece(Type type, Colour colour) {
    if (colour == Colour::Black) {
        for (auto piece : this->black) {
            if (piece->getType() == type) {
                return piece;
            }
        }
    } else {
        for (auto piece : this->white) {
            if (piece->getType() == type) {
                return piece;
            }
        }
    }
    return nullptr;
}

// remove piece from grid
// this method does not clean up memory!
void Grid::removePiece(Piece* piece) {
    for (unsigned int i = 0; i < this->black.size(); ++i) {
        if (this->black.at(i) == piece) {
            this->black.erase(this->black.begin() + i);
        }
    }
    for (unsigned int i = 0; i < this->white.size(); ++i) {
        if (this->white.at(i) == piece) {
            this->white.erase(this->white.begin() + i);
        }
    }
    for (unsigned int i = 0; i < this->grid.size(); ++i) {
        for (unsigned int j = 0; j < this->grid.at(i).size(); ++j) {
            if (this->getPiece(i, j) == piece) {
                this->grid.at(i).at(j).setPiece(nullptr);
            }
        }
    }

}

// remove piece at (r, c) from grid
// this method does clean up memory
void Grid::removePiece(int r, int c) {
    Piece* piece = this->getPiece(r, c);
    this->removePiece(piece);
    this->td->update(*this);
    delete piece;
}

Result Grid::checkmate() {
    return Result::InGame;
}

void Grid::notify(Subject& whoFrom) {
    // downcast from subject to a piece (whoFrom MUST be class Piece)
    Piece& piece = static_cast<Piece&>(whoFrom);
}

Grid::~Grid() {

}

void computerBestMove(Colour colour, int level) {
    // first decide if there is any check
    // if there is no check, decide if there is any capture move
    // if there is no capture move, make a random move
}