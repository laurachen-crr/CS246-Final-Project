#include "grid.h"
#include "textdisplay.h"
#include "utils.h"
#include "exception.h"
#include "enums.h"

Grid::Grid() {
    for(int i = 0; i < 8; ++i) {
        this->white.emplace_back(Piece::createPiece(1, i, Colour::White, Type::Pawn));
        this->black.emplace_back(Piece::createPiece(6, i, Colour::Black, Type::Pawn));
    }

    this->black.emplace_back(Piece::createPiece(7, 0, Colour::Black, Type::Rook));
    this->black.emplace_back(Piece::createPiece(7, 1, Colour::Black, Type::Knight));
    this->black.emplace_back(Piece::createPiece(7, 2, Colour::Black, Type::Bishop));
    this->black.emplace_back(Piece::createPiece(7, 3, Colour::Black, Type::Queen));
    this->black.emplace_back(Piece::createPiece(7, 4, Colour::Black, Type::King));
    this->black.emplace_back(Piece::createPiece(7, 5, Colour::Black, Type::Bishop));
    this->black.emplace_back(Piece::createPiece(7, 6, Colour::Black, Type::Knight));
    this->black.emplace_back(Piece::createPiece(7, 7, Colour::Black, Type::Rook));

    this->white.emplace_back(Piece::createPiece(0, 0, Colour::White, Type::Rook));
    this->white.emplace_back(Piece::createPiece(0, 1, Colour::White, Type::Knight));
    this->white.emplace_back(Piece::createPiece(0, 2, Colour::White, Type::Bishop));
    this->white.emplace_back(Piece::createPiece(0, 3, Colour::White, Type::Queen));
    this->white.emplace_back(Piece::createPiece(0, 4, Colour::White, Type::King));
    this->white.emplace_back(Piece::createPiece(0, 5, Colour::White, Type::Bishop));
    this->white.emplace_back(Piece::createPiece(0, 6, Colour::White, Type::Knight));
    this->white.emplace_back(Piece::createPiece(0, 7, Colour::White, Type::Rook));

    this->td = new TextDisplay{};
    this->gd = new GraphicsDisplay{};
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
    // update textdisplay and graphic display
    this->td->update(*this);
    this->gd->updateGrid(*this);

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

// get piece at (r, c)
Piece* Grid::getPiece(int r, int c) {
    return this->getCell(r, c).getPiece();
}

// get cell at (r, c)
Cell& Grid::getCell(int r, int c) {
    return this->grid.at(r).at(c);
} 

std::ostream &operator<<(std::ostream &out, const Grid &g) {
    out << *g.td;
    return out;
}

bool Grid::move(Colour colour, int fromR, int fromC, int toR, int toC) {
    Piece* oldPiece = this->getPiece(fromR, fromC);
    // piece that user specified doesn't exist
    if (oldPiece == nullptr) {
        return false;
    }

    // piece must be same colour as the player
    Colour pieceColour = oldPiece->getColour();
    if (pieceColour != colour) {
        return false;
    }

    // Check for valid move
    if (!(this->getPiece(fromR,fromC)->checkValidMove(toR,toC,*this))) {
        return false;
    }

    // Check for checkmate

    Piece* temp = this->getPiece(toR, toC);

    // set piece at new location
    this->removePiece(oldPiece);
    this->setPiece(toR, toC, oldPiece);
    delete temp;
    this->td->update(*this);
    this->gd->updateGrid(*this);
    return true;
}

// return if you move piece to pos results in a check
Colour Grid::check(Piece* piece, Pos pos) {
    Pos piecePos = piece->getPos();
    Cell& pieceCell = this->getCell(piecePos.row, piecePos.col);
    if (piecePos.col == pos.col && piecePos.row == pos.row) {
        return this->check();
    } else {
        Piece* curPiece = this->getPiece(pos.row, pos.col);
        Cell& curCell = this->getCell(pos.row, pos.col);
        pieceCell.removePiece();
        curCell.setPiece(piece);
        Colour c = this->check();
        curCell.setPiece(curPiece);
        pieceCell.setPiece(piece);
        return c;
    }
}

// return if the current board has a check
Colour Grid::check() {
    cout << "A" << endl;
    Pos blackKingPos = this->findPiece(Type::King, Colour::Black)->getPos();
    Pos whiteKingPos = this->findPiece(Type::King, Colour::White)->getPos();

    cout << "B" << endl;
    for (auto p : this->white) {
         cout << "C" << endl;
        vector<Pos> allPossibleMoves = p->getValidMoves(*this);
        cout << "D" << endl;
        if (Utils::posInVector(allPossibleMoves, blackKingPos)) {
            cout << "E" << endl;
            return Colour::Black;
        }
    }
    for (auto p : this->black) {
        vector<Pos> allPossibleMoves = p->getValidMoves(*this);
        if (Utils::posInVector(allPossibleMoves, whiteKingPos)) {
            return Colour::White;
        }
    }
    return Colour::NoColour;
}

// sets newPiece at (r, c)
// this method does not clean up memory or validate!
// use this for general purposes
void Grid::setPiece(int r, int c, Piece* newPiece) {
    Piece* oldPiece = this->getPiece(r, c);
    this->removePiece(oldPiece);
    this->getCell(r, c).setPiece(newPiece);
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
// ONLY use this for setup mode!!
bool Grid::setPiece(Colour colour, int r, int c, Type type) {
    Piece* oldPiece = this->getPiece(r, c);
    Piece* newPiece = Piece::createPiece(r, c, colour, type);
    this->setPiece(r, c, newPiece);
    if (this->check() != Colour::NoColour) { // in check
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
        this->gd->updateGrid(*this);
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

// remove piece from grid and vectors
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
    for (unsigned int r = 0; r < this->grid.size(); ++r) {
        for (unsigned int c = 0; c < this->grid.at(r).size(); ++c) {
            if (this->getPiece(r, c) == piece) {
                this->getCell(r, c).removePiece();
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
    this->gd->updateGrid(*this);
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
    // free every piece in black vector
    for (auto piece : this->black) {
        delete piece;
    }

    // free every piece in white vector
    for (auto piece : this->white) {
        delete piece;
    }

    // free text display
    delete this->td;

    // free graph display
    delete this->gd;
}

void computerBestMove(Colour colour, int level) {
    // first decide if there is any check
    // if there is no check, decide if there is any capture move
    // if there is no capture move, make a random move
}

