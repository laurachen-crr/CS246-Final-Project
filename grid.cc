#include "grid.h"

#include "enums.h"
#include "exception.h"
#include "textdisplay.h"
#include "utils.h"

Grid::Grid(bool text) {
    this->td = new TextDisplay{};
    if (text) {
        this->gd = nullptr;
    } else {
        this->gd = new GraphicsDisplay{};
    }
}

void Grid::init(bool empty) {
    // reset pieces
    for (auto piece : this->white) {
        delete piece;
    }

    for (auto piece : this->black) {
        delete piece;
    }

    this->white.clear();
    this->black.clear();

    // create all pieces
    if (!empty) {
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
    }

    // reset board
    this->grid.clear();

    for (int i = 0; i < 8; ++i) {
        this->grid.emplace_back(vector<Cell>{});
        for (int j = 0; j < 8; ++j) {
            this->grid.at(i).emplace_back(Cell{i, j});
        }
    }

    // init all the pieces
    if (!empty) {
        for (int i = 0; i < 8; ++i) {
            this->grid.at(0).at(i).setPiece(this->black.at(i + 8));
            this->grid.at(1).at(i).setPiece(this->black.at(i));
            this->grid.at(6).at(i).setPiece(this->white.at(i));
            this->grid.at(7).at(i).setPiece(this->white.at(i + 8));
        }
    }

    // update
    this->td->update(*this);
    if (this->gd != nullptr) {
        this->gd->update(*this);
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

// main move command
bool Grid::move(Colour colour, int fromR, int fromC, int toR, int toC,
                Type promotion) {
    // positions must be on the board
    if (!Utils::onBoard(fromR, fromC) || !Utils::onBoard(toR, toC)) {
        return false;
    }
    Piece* fromPiece = this->getPiece(fromR, fromC);
    Piece* toPiece = this->getPiece(toR, toC);

    // piece that user specified doesn't exist
    if (fromPiece == nullptr) {
        return false;
    }

    // piece must be same colour as the player
    Colour pieceColour = fromPiece->getColour();
    if (pieceColour != colour) {
        return false;
    }

    // check for valid move
    if (!(fromPiece->checkValidMove(toR, toC, *this))) {
        // check for castling
        if (checkCastling(colour, fromR, fromC, toR, toC)) {
            this->setPiece(toR, toC, fromPiece);
            this->setPiece(fromR, fromC, toPiece);

            // update
            this->td->update(*this);
            if (this->gd != nullptr) {
                this->gd->update(*this);
            }

            this->lastMove = this->getPiece(toR, toC);
            fromPiece->setPrev({fromR, fromC});
            toPiece->setPrev({toR, toC});
            return true;
        } else {
            return false;
        }
    }

    // promotion validation
    if (fromPiece->getType() == Type::Pawn) {
        if (pieceColour == Colour::Black && toR == 7) {
            if (promotion == Type::NoType || promotion == Type::Pawn ||
                promotion == Type::King) {
                return false;
            }
        } else if (pieceColour == Colour::White && toR == 0) {
            if (promotion == Type::NoType || promotion == Type::Pawn ||
                promotion == Type::King) {
                return false;
            }
        }
    } else if (promotion != Type::NoType) {
        return false;
    }

    // set piece at new location
    this->setPiece(toR, toC, fromPiece);
    delete toPiece;

    // promote if needed
    if (promotion != Type::NoType) {
        this->setPiece(pieceColour, toR, toC, promotion);
        fromPiece = this->getPiece(toR, toC);
    }

    // update
    this->td->update(*this);
    if (this->gd != nullptr) {
        this->gd->update(*this);
    }

    this->lastMove = this->getPiece(toR, toC);
    fromPiece->setPrev({fromR, fromC});
    return true;
}

bool Grid::checkCastling(Colour colour, int fromR, int fromC, int toR,
                         int toC) {
    Piece* fromPiece = this->getPiece(fromR, fromC);
    Piece* toPiece = this->getPiece(toR, toC);
    if (fromPiece == nullptr && toPiece == nullptr) {
        return false;
    }

    if (fromPiece->getType() == Type::King &&
        toPiece->getType() == Type::Rook &&
        toPiece->getColour() == fromPiece->getColour() &&
        fromPiece->getPrev() == Pos{-1, -1} &&
        toPiece->getPrev() == Pos{-1, -1}) {
        if (fromC < toC) {
            if (this->getPiece(fromR, fromC + 1) == nullptr &&
                this->getPiece(fromR, fromC + 2) == nullptr) {
                if (!check(fromPiece, fromPiece->getPos()) &&
                    !check(fromPiece, {fromR, fromC + 1}) &&
                    !check(fromPiece, {fromR, fromC + 2}) &&
                    !check(toPiece, toPiece->getPos())) {
                    return true;
                }
            }
        } else {
            if (this->getPiece(fromR, fromC - 1) == nullptr &&
                this->getPiece(fromR, fromC - 2) == nullptr &&
                this->getPiece(fromR, fromC - 3) == nullptr) {
                if (!check(fromPiece, fromPiece->getPos()) &&
                    !check(fromPiece, {fromR, fromC - 1}) &&
                    !check(fromPiece, {fromR, fromC - 2}) &&
                    !check(fromPiece, {fromR, fromC - 3}) &&
                    !check(toPiece, toPiece->getPos())) {
                    return true;
                }
            }
        }
    }
    return false;
}


// check by moving piece to pos results in a check for yourself
bool Grid::check(Piece* piece, Pos pos) {
    Pos piecePos = piece->getPos();
    Colour colour = piece->getColour();
    bool inCheck;

    if (piecePos == pos) {
        inCheck = this->check(colour, false);
    } else {
        Piece* curPiece = this->getPiece(pos.row, pos.col);

        // move new piece to pos
        this->setPiece(pos.row, pos.col, piece);

        // see if in check after move
        inCheck = this->check(colour, false);

        // put old and new piece back
        this->setPiece(pos.row, pos.col, curPiece);
        this->setPiece(piecePos.row, piecePos.col, piece);
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
        if (Utils::inVector(moves, king->getPos())) {
            return true;
        }
    }

    return false;
}

// sets newPiece at (r, c)
// this method does not clean up memory or validate!
// use this for general purposes
// note this removes the original piece at (r, c) completely
void Grid::setPiece(int r, int c, Piece* newPiece) {
    Piece* oldPiece = this->getPiece(r, c);
    this->removePiece(oldPiece);
    this->removePiece(newPiece);
    this->getCell(r, c).setPiece(newPiece);
    if (newPiece != nullptr) {
        vector<Piece*>& pieces = this->getPieces(newPiece->getColour());
        if (!Utils::inVector(pieces, newPiece)) {
            pieces.emplace_back(newPiece);
        }
    }
}

// creates new piece at (r, c) and replace old piece
// this method cleans up memory and validates
void Grid::setPiece(Colour colour, int r, int c, Type type) {
    Piece* oldPiece = this->getPiece(r, c);
    Piece* newPiece = Piece::createPiece(r, c, colour, type);
    this->setPiece(r, c, newPiece);
    delete oldPiece;
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

// for setup mode
void Grid::setupSetPiece(Colour colour, int r, int c, Type type) {
    this->setPiece(colour, r, c, type);
    // update
    this->td->update(*this);
    if (this->gd != nullptr) {
        this->gd->update(*this);
    }
}

// for setup mode
void Grid::setupRemovePiece(int r, int c) {
    this->removePiece(r, c);
    // update
    this->td->update(*this);
    if (this->gd != nullptr) {
        this->gd->update(*this);
    }
}

// remove piece at (r, c) from grid
// this method does clean up memory
void Grid::removePiece(int r, int c) {
    Piece* piece = this->getPiece(r, c);
    this->removePiece(piece);
    delete piece;
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
Result Grid::checkmate() {
    Colour colour;  // colour that is in check right now
    if (this->check(Colour::White)) {
        colour = Colour::White;
    } else if (this->check(Colour::Black)) {
        colour = Colour::Black;
    } else {
        // check if stalemate
        for (auto piece : this->black) {
            vector<Pos> moves = piece->getValidMoves(*this);
            if (moves.size() != 0) {
                return Result::InGame;
            }
        }

        for (auto piece : this->white) {
            vector<Pos> moves = piece->getValidMoves(*this);
            if (moves.size() != 0) {
                return Result::InGame;
            }
        }

        return Result::Stalemate;
    }

    // check if there's any move that can avoid check (ie. try all moves)
    vector<Piece*>& pieces = this->getPieces(colour);

    for (auto piece : pieces) {
        vector<Pos> moves = piece->getValidMoves(*this);
        for (auto pos : moves) {
            if (!this->check(piece, pos)) {
                return Result::InGame;
            }
        }
    }

    // checkmate
    if (colour == Colour::White) {
        return Result::BlackWin;
    } else {
        return Result::WhiteWin;
    }
}

GraphicsDisplay* Grid::getGraphicsDisplay() {
    return this->gd;
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
