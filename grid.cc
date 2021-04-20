#include "grid.h"

#include "enums.h"
#include "exception.h"
#include "textdisplay.h"
#include "utils.h"

Grid::Grid() {
    for (int i = 0; i < 8; ++i) {
        this->white.emplace_back(
            Piece::createPiece(1, i, Colour::White, Type::Pawn));
        this->black.emplace_back(
            Piece::createPiece(6, i, Colour::Black, Type::Pawn));
    }

    this->black.emplace_back(
        Piece::createPiece(7, 0, Colour::Black, Type::Rook));
    this->black.emplace_back(
        Piece::createPiece(7, 1, Colour::Black, Type::Knight));
    this->black.emplace_back(
        Piece::createPiece(7, 2, Colour::Black, Type::Bishop));
    this->black.emplace_back(
        Piece::createPiece(7, 3, Colour::Black, Type::Queen));
    this->black.emplace_back(
        Piece::createPiece(7, 4, Colour::Black, Type::King));
    this->black.emplace_back(
        Piece::createPiece(7, 5, Colour::Black, Type::Bishop));
    this->black.emplace_back(
        Piece::createPiece(7, 6, Colour::Black, Type::Knight));
    this->black.emplace_back(
        Piece::createPiece(7, 7, Colour::Black, Type::Rook));

    this->white.emplace_back(
        Piece::createPiece(0, 0, Colour::White, Type::Rook));
    this->white.emplace_back(
        Piece::createPiece(0, 1, Colour::White, Type::Knight));
    this->white.emplace_back(
        Piece::createPiece(0, 2, Colour::White, Type::Bishop));
    this->white.emplace_back(
        Piece::createPiece(0, 3, Colour::White, Type::Queen));
    this->white.emplace_back(
        Piece::createPiece(0, 4, Colour::White, Type::King));
    this->white.emplace_back(
        Piece::createPiece(0, 5, Colour::White, Type::Bishop));
    this->white.emplace_back(
        Piece::createPiece(0, 6, Colour::White, Type::Knight));
    this->white.emplace_back(
        Piece::createPiece(0, 7, Colour::White, Type::Rook));

    this->td = new TextDisplay{};
}

void Grid::init() {
    for (int i = 0; i < 8; ++i) {
        this->grid.emplace_back(vector<Cell>{});
        for (int j = 0; j < 8; ++j) {
            this->grid.at(i).emplace_back(Cell{i, j});
        }
    }
    // init all the pieces
    for (int i = 0; i < 8; ++i) {
        this->grid.at(0).at(i).setPiece(this->black.at(i + 8));
        this->grid.at(1).at(i).setPiece(this->black.at(i));
        this->grid.at(6).at(i).setPiece(this->white.at(i));
        this->grid.at(7).at(i).setPiece(this->white.at(i + 8));
    }
    // update textdisplay
    this->td->update(*this);

    // attach observers(all pieces) to the grid
    for (int i = 0; i < 16; ++i) {
        this->attach(this->black.at(i));
        this->attach(this->black.at(i));
    }

    // attach grid to pieces as observer
    for (int i = 0; i < 16; ++i) {
        this->black.at(i)->attach(this);
        this->white.at(i)->attach(this);
    }
}

// get piece at (r, c)
Piece* Grid::getPiece(int r, int c) { return this->getCell(r, c).getPiece(); }

// get cell at (r, c)
Cell& Grid::getCell(int r, int c) { return this->grid.at(r).at(c); }

std::ostream& operator<<(std::ostream& out, const Grid& g) {
    out << *g.td;
    return out;
}

bool Grid::move(Colour colour, int fromR, int fromC, int toR, int toC) {
    cout << "move to: " << toR << " : " << toC << endl;
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
    if (!(oldPiece->checkValidMove(toR, toC, *this))) {
        return false;
    }

    // Check for checkmate

    Piece* temp = this->getPiece(toR, toC);

    // set piece at new location
    this->removePiece(oldPiece);
    this->setPiece(toR, toC, oldPiece);
    delete temp;
    this->td->update(*this);
    return true;
}

// check by moving piece to pos results in a check for yourself
bool Grid::check(Piece* piece, Pos pos) {
    Pos piecePos = piece->getPos();
    Colour colour = piece->getColour();
    bool inCheck;
    Cell& pieceCell = this->getCell(piecePos.row, piecePos.col);
    if (piecePos.col == pos.col && piecePos.row == pos.row) {
        inCheck = this->check(colour, false);
    } else {
        Piece* curPiece = this->getPiece(pos.row, pos.col);
        Cell& curCell = this->getCell(pos.row, pos.col);
        this->removePiece(curPiece);
        curCell.setPiece(piece);
        inCheck = this->check(colour, false);
        this->setPiece(pos.row, pos.col, curPiece);
        pieceCell.setPiece(piece);
    }
    return inCheck;
}

// return if the current board has a check for colour
bool Grid::check(Colour colour, bool check) {
    Piece* king = this->findPiece(Type::King, colour);
    if (king == nullptr) {
        return false;
    }
    vector<Piece*>& pieces = this->getPieces(Utils::opponent(colour));

    for (auto piece : pieces) {
        vector<Pos> moves = piece->getValidMoves(*this, check);
        if (Utils::posInVector(moves, king->getPos())) {
            return true;
        }
    }

    return false;
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
// this method cleans up memory and validates
// ONLY use this for setup mode!!
void Grid::setPiece(Colour colour, int r, int c, Type type) {
    Piece* oldPiece = this->getPiece(r, c);
    Piece* newPiece = Piece::createPiece(r, c, colour, type);
    this->setPiece(r, c, newPiece);
    delete oldPiece;
    this->td->update(*this);
}

// determines if setup is valid
bool Grid::validateSetup() {
    // in check
    if (this->check(Colour::White) || this->check(Colour::Black)) {
        return false;
    }

    // pawn on last/first row 
    int bKingCount = 0;
    for (auto piece : this->black) {
        int row = piece->getPos().row;
        if (piece->getType() == Type::Pawn && (row == 0 || row == 7)) {
            return false;
        } else if (piece->getType() == Type::King) {
            bKingCount++;
        }
    }

    int wKingCount = 0;
    for (auto piece : this->white) {
        int row = piece->getPos().row;
        if (piece->getType() == Type::Pawn && (row == 0 || row == 7)) {
            return false;
        } else if (piece->getType() == Type::King) {
            wKingCount++;
        }
    }

    // more or less than one king
    if (bKingCount != 1 || wKingCount != 1) {
        return false;
    }

    return true;
}

// return first found piece that match type and colour
Piece* Grid::findPiece(Type type, Colour colour) {
    vector<Piece*>& pieces = this->getPieces(colour);
    for (auto piece : pieces) {
        if (piece->getType() == type) {
            return piece;
        }
    }
    return nullptr;
}

// remove piece from grid and vectors
// this method does not clean up memory!
void Grid::removePiece(Piece* piece) {
    if (piece == nullptr) {
        return;
    }
    vector<Piece*>& pieces = this->getPieces(piece->getColour());
    for (unsigned int i = 0; i < pieces.size(); ++i) {
        if (pieces.at(i) == piece) {
            pieces.erase(pieces.begin() + i);
            break;
        }
    }
    for (unsigned int r = 0; r < this->grid.size(); ++r) {
        for (unsigned int c = 0; c < this->grid.at(r).size(); ++c) {
            if (this->getPiece(r, c) == piece) {
                this->getCell(r, c).removePiece();
                break;
            }
        }
    }
}

// remove piece at (r, c) from grid
// this method does clean up memory
void Grid::removePiece(int r, int c) {
    Piece* piece = this->getPiece(r, c);
    this->removePiece(piece);
    delete piece;
    this->td->update(*this);
}

// return array of pieces based on colour
vector<Piece*>& Grid::getPieces(Colour colour) {
    if (colour == Colour::White) {
        return this->white;
    } else {
        return this->black;
    }
}

// return the state of the game
// NEED TO ADD: check for stalemate
Result Grid::checkmate() {
    Piece* king;
    Colour colour;
    if (this->check(Colour::White)) {
        colour = Colour::White;
        king = this->findPiece(Type::King, Colour::White);
    } else if (this->check(Colour::Black)) {
        colour = Colour::Black;
        king = this->findPiece(Type::King, Colour::Black);
        ;
    } else {
        return Result::InGame;
    }

    // check if king has valid moves to avoid check
    vector<Pos> moves = king->getValidMoves(*this);
    for (auto pos : moves) {
        if (!this->check(king, pos)) {
            return Result::InGame;
        }
    }

    // get the piece(s) currently putting the king in check
    vector<Piece*>& pieces = this->getPieces(Utils::opponent(colour));
    vector<Piece*> checks;

    for (auto piece : pieces) {
        moves = piece->getValidMoves(*this);
        if (Utils::posInVector(moves, king->getPos())) {
            checks.emplace_back(piece);
        }
    }

    // if there are more then one piece keeping king in check, it is a checkmate
    if (checks.size() != 1) {
        if (colour == Colour::White) {
            return Result::BlackWin;
        } else {
            return Result::WhiteWin;
        }
    }

    // check if there's any piece that can block for the king
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
}

void computerBestMove(Colour colour, int level) {
    // first decide if there is any check
    // if there is no check, decide if there is any capture move
    // if there is no capture move, make a random move
}
