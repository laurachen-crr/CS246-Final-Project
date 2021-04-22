#include "piece.h"
#include <vector>
#include "grid.h"
#include "utils.h"
using namespace std;

// helper for rook
int validMove(Grid& g, int atR, int atC, Colour colour) {
    Piece* currPiece = g.getPiece(atR, atC);
    if (currPiece == nullptr) {  // no piece at cell
        return 0;                // legal move
    } else {
        Colour currColour =
            currPiece->getColour();  // get colour of piece at cell atR, atC
        if (colour ==
            currColour) {  // colour of atR,atC is the same as piece in question
            return 1;      // illegal
        } else {
            return 2;  // legal but stop here
        }
    }
}

Piece::Piece(int row, int col, Colour colour, Type type) {
    this->pos = {row, col};
    this->colour = colour;
    this->type = type;
    this->prev = {-1, -1};
}

Piece::~Piece() {};

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

bool King::checkValidMove(int r, int c, Grid& g) {
    Pos destination = {r, c};
    vector<Pos> allValidMoves = this->getValidMoves(g);
    return Utils::inVector(allValidMoves, destination);
}

bool Queen::checkValidMove(int r, int c, Grid& g) {
    Pos destination = {r, c};
    vector<Pos> allValidMoves = this->getValidMoves(g);
    return Utils::inVector(allValidMoves, destination);
}

bool Bishop::checkValidMove(int r, int c, Grid& g) {
    Pos destination = {r, c};
    vector<Pos> allValidMoves = this->getValidMoves(g);
    return Utils::inVector(allValidMoves, destination);
}

bool Pawn::checkValidMove(int r, int c, Grid& g) {
    Pos destination = {r, c};
    vector<Pos> allValidMoves = this->getValidMoves(g);
    return Utils::inVector(allValidMoves, destination);
}

bool Rook::checkValidMove(int r, int c, Grid& g) {
    Pos destination = {r, c};
    vector<Pos> allValidMoves = this->getValidMoves(g);
    return Utils::inVector(allValidMoves, destination);
}

bool Knight::checkValidMove(int r, int c, Grid& g) {
    Pos destination = {r, c};
    vector<Pos> allValidMoves = this->getValidMoves(g);
    return Utils::inVector(allValidMoves, destination);
}

vector<Pos> King::getValidMoves(Grid& g, bool check) {
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
                    if (!check || !g.check(this, pos)) {
                        allValidMoves.push_back(pos);
                    }
                }
            }
        }
    }

    // bool castling = true;
    // if(this->firstMove) { // king first move
    //     if(g.getPiece(row, 0) != nullptr && g.getPiece(row, 0)->getType() == Type::Rook && g.getPiece().firstMove) {
    //         for(int i = col-1; i--; )
    //     }
    // }
    return allValidMoves;
}

vector<Pos> Queen::getValidMoves(Grid& g, bool check) {
    vector<Pos> validMoves;

    Pos curPos = this->getPos();
    int row = curPos.row;
    int col = curPos.col;

    // loop diagonally
    for (int i = 0; i <= 3; ++i) {
        int offsetRow = 0;
        int offsetCol = 0;
        int incrementRow = 0;
        int incrementCol = 0;
        switch (i) {
            case 0:  // up right
                offsetRow = 1;
                offsetCol = 1;
                incrementRow = 1;
                incrementCol = 1;
                break;
            case 1:  // down right
                offsetRow = -1;
                offsetCol = 1;
                incrementRow = -1;
                incrementCol = 1;
                break;
            case 2:  // up left
                offsetRow = 1;
                offsetCol = -1;
                incrementRow = 1;
                incrementCol = -1;
                break;
            case 3:  // down left
                offsetRow = -1;
                offsetCol = -1;
                incrementRow = -1;
                incrementCol = -1;
                break;
        }

        while (Utils::onBoard(row + offsetRow, col + offsetCol)) {
            Piece* curPiece = g.getPiece(row + offsetRow, col + offsetCol);
            Pos pos = {row + offsetRow, col + offsetCol};

            if (curPiece != nullptr) {
                // can't jump over own piece
                if (curPiece->getColour() == this->getColour()) {
                    break;
                } else {
                    if (!check || !g.check(this, pos)) {
                        validMoves.push_back(pos);
                    }
                    break;
                }
            } else {  // empty spot
                if (!check || !g.check(this, pos)) {
                    validMoves.push_back(pos);
                }
            }
            offsetRow += incrementRow;
            offsetCol += incrementCol;
        }
    }

    // loop horizontally and vertically
    for (int i = 0; i <= 3; ++i) {
        int offsetRow = 0;
        int offsetCol = 0;
        int incrementRow = 0;
        int incrementCol = 0;
        switch (i) {
            case 0:  // up
                offsetRow = 1;
                incrementRow = 1;
                break;
            case 1:  // down
                offsetRow = -1;
                incrementRow = -1;
                break;
            case 2:  // right
                offsetCol = 1;
                incrementCol = 1;
                break;
            case 3:  // left
                offsetCol = -1;
                incrementCol = -1;
                break;
        }

        while (Utils::onBoard(row + offsetRow, col + offsetCol)) {
            Piece* curPiece = g.getPiece(row + offsetRow, col + offsetCol);
            Pos pos = {row + offsetRow, col + offsetCol};

            if (curPiece != nullptr) {
                // can't jump over own piece
                if (curPiece->getColour() == this->getColour()) {
                    break;
                } else {
                    if (!check || !g.check(this, pos)) {
                        validMoves.push_back(pos);
                    }
                    break;
                }
            } else {  // empty spot
                if (!check || !g.check(this, pos)) {
                    validMoves.push_back(pos);
                }
            }
            offsetRow += incrementRow;
            offsetCol += incrementCol;
        }
    }

    return validMoves;
}

vector<Pos> Bishop::getValidMoves(Grid& g, bool check) {
    vector<Pos> validMoves;

    Pos curPos = this->getPos();
    int row = curPos.row;
    int col = curPos.col;

    // loop diagonally
    for (int i = 0; i <= 3; ++i) {
        int offsetRow = 0;
        int offsetCol = 0;
        int incrementRow = 0;
        int incrementCol = 0;
        switch (i) {
            case 0:  // up right
                offsetRow = 1;
                offsetCol = 1;
                incrementRow = 1;
                incrementCol = 1;
                break;
            case 1:  // down right
                offsetRow = -1;
                offsetCol = 1;
                incrementRow = -1;
                incrementCol = 1;
                break;
            case 2:  // up left
                offsetRow = 1;
                offsetCol = -1;
                incrementRow = 1;
                incrementCol = -1;
                break;
            case 3:  // down left
                offsetRow = -1;
                offsetCol = -1;
                incrementRow = -1;
                incrementCol = -1;
                break;
        }

        while (Utils::onBoard(row + offsetRow, col + offsetCol)) {
            Piece* curPiece = g.getPiece(row + offsetRow, col + offsetCol);
            Pos pos = {row + offsetRow, col + offsetCol};

            if (curPiece != nullptr) {
                // can't jump over own piece
                if (curPiece->getColour() == this->getColour()) {
                    break;
                } else {
                    if (!check || !g.check(this, pos)) {
                        validMoves.push_back(pos);
                    }
                    break;
                }
            } else {  // empty spot
                if (!check || !g.check(this, pos)) {
                    validMoves.push_back(pos);
                }
            }
            offsetRow += incrementRow;
            offsetCol += incrementCol;
        }
    }

    return validMoves;
}

vector<Pos> Pawn::getValidMoves(Grid& g, bool check) {
    int row = this->getPos().row;
    int col = this->getPos().col;
    vector<Pos> allValidMoves;

    if (this->getColour() == Colour::White) {
        if (row != 0) {
            if (g.getPiece(row - 1, col) == nullptr) {
                Pos pos = {row - 1, col};
                if (!check || !g.check(this, pos)) {
                    allValidMoves.push_back(pos);
                }
            }

            if (Utils::onBoard(row - 1, col + 1)) {
                if (g.getPiece(row - 1, col + 1) != nullptr &&
                    g.getPiece(row - 1, col + 1)->getColour() ==
                        Colour::Black) {
                    Pos pos = {row - 1, col + 1};
                    if (!check || !g.check(this, pos)) {
                        allValidMoves.push_back(pos);
                    }
                }
            } 
            
            if (Utils::onBoard(row - 1, col - 1)) {
                if (g.getPiece(row - 1, col - 1) != nullptr &&
                    g.getPiece(row - 1, col - 1)->getColour() ==
                        Colour::Black) {
                    Pos pos = {row - 1, col - 1};
                    if (!check || !g.check(this, pos)) {
                        allValidMoves.push_back(pos);
                    }
                }
            }

            if (row == 6) {
                if (g.getPiece(4, col) == nullptr && g.getPiece(5, col) == nullptr) {
                    Pos pos = {4, col};
                    if (!check || !g.check(this, pos)) {
                        allValidMoves.push_back(pos);
                    }
                }
            }
        }
    } else {
        if (row != 7) {
            if (g.getPiece(row + 1, col) == nullptr) {
                Pos pos = {row + 1, col};
                if (!check || !g.check(this, pos)) {
                    allValidMoves.push_back(pos);
                }
            }

            if (Utils::onBoard(row + 1, col + 1)) {
                if (g.getPiece(row + 1, col + 1) != nullptr &&
                    g.getPiece(row + 1, col + 1)->getColour() ==
                        Colour::White) {
                    Pos pos = {row + 1, col + 1};
                    if (!check || !g.check(this, pos)) {
                        allValidMoves.push_back(pos);
                    }
                }
            } 
            
            if (Utils::onBoard(row + 1, col - 1)) {
                if (g.getPiece(row + 1, col - 1) != nullptr &&
                    g.getPiece(row + 1, col - 1)->getColour() ==
                        Colour::White) {
                    Pos pos = {row + 1, col - 1};
                    if (!check || !g.check(this, pos)) {
                        allValidMoves.push_back(pos);
                    }
                }
            }

            if (row == 1) {
                if (g.getPiece(3, col) == nullptr && g.getPiece(2, col) == nullptr) {
                    Pos pos = {3, col};
                    if (!check || !g.check(this, pos)) {
                        allValidMoves.push_back(pos);
                    }
                }
            }
        }
    }



    return allValidMoves;
}

vector<Pos> Knight::getValidMoves(Grid& g, bool check) {
    int row = this->getPos().row;
    int col = this->getPos().col;
    vector<Pos> allValidMoves;

    if (Utils::onBoard(row + 2, col + 1)) {
        if (!(g.getPiece(row + 2, col + 1) != nullptr &&
              g.getPiece(row + 2, col + 1)->getColour() == this->getColour())) {
            Pos pos = {row + 2, col + 1};
            if (!check || !g.check(this, pos)) {
                allValidMoves.push_back(pos);
            }
        }
    } 
    
    if (Utils::onBoard(row - 2, col + 1)) {
        if (!(g.getPiece(row - 2, col + 1) != nullptr &&
              g.getPiece(row - 2, col + 1)->getColour() == this->getColour())) {
            Pos pos = {row - 2, col + 1};
            if (!check || !g.check(this, pos)) {
                allValidMoves.push_back(pos);
            }
        }
    } 
    
    if (Utils::onBoard(row + 2, col - 1)) {
        if (!(g.getPiece(row + 2, col - 1) != nullptr &&
              g.getPiece(row + 2, col - 1)->getColour() == this->getColour())) {
            Pos pos = {row + 2, col - 1};
            if (!check || !g.check(this, pos)) {
                allValidMoves.push_back(pos);
            }
        }
    } 
    
    if (Utils::onBoard(row - 2, col - 1)) {
        if (!(g.getPiece(row - 2, col - 1) != nullptr &&
              g.getPiece(row - 2, col - 1)->getColour() == this->getColour())) {
            Pos pos = {row - 2, col - 1};
            if (!check || !g.check(this, pos)) {
                allValidMoves.push_back(pos);
            }
        }
    }

    ////////////

    if (Utils::onBoard(row + 1, col + 2)) {
        if (!(g.getPiece(row + 1, col + 2) != nullptr &&
              g.getPiece(row + 1, col + 2)->getColour() == this->getColour())) {
            Pos pos = {row + 1, col + 2};
            if (!check || !g.check(this, pos)) {
                allValidMoves.push_back(pos);
            }
        }
    } 
    
    if (Utils::onBoard(row - 1, col + 2)) {
        if (!(g.getPiece(row - 1, col + 2) != nullptr &&
              g.getPiece(row - 1, col + 2)->getColour() == this->getColour())) {
            Pos pos = {row - 1, col + 2};
            if (!check || !g.check(this, pos)) {
                allValidMoves.push_back(pos);
            }
        }
    } 
    
    if (Utils::onBoard(row + 1, col - 2)) {
        if (!(g.getPiece(row + 1, col - 2) != nullptr &&
              g.getPiece(row + 1, col - 2)->getColour() == this->getColour())) {
            Pos pos = {row + 1, col - 2};
            if (!check || !g.check(this, pos)) {
                allValidMoves.push_back(pos);
            }
        }
    } 
    
    if (Utils::onBoard(row - 1, col - 2)) {
        if (!(g.getPiece(row - 1, col - 2) != nullptr &&
              g.getPiece(row - 1, col - 2)->getColour() == this->getColour())) {
            Pos pos = {row - 1, col - 2};
            if (!check || !g.check(this, pos)) {
                allValidMoves.push_back(pos);
            }
        }
    }
    if(check) {
        for(auto pos : allValidMoves) {
            cout << pos.row << " : " << pos.col << endl;
        }
    }
    
    return allValidMoves;
}

vector<Pos> Rook::getValidMoves(Grid& g, bool check) {
    vector<Pos> validMoves;

    Pos curPos = this->getPos();
    int row = curPos.row;
    int col = curPos.col;

    // loop horizontally and vertically
    for (int i = 0; i <= 3; ++i) {
        int offsetRow = 0;
        int offsetCol = 0;
        int incrementRow = 0;
        int incrementCol = 0;
        switch (i) {
            case 0:  // up
                offsetRow = 1;
                incrementRow = 1;
                break;
            case 1:  // down
                offsetRow = -1;
                incrementRow = -1;
                break;
            case 2:  // right
                offsetCol = 1;
                incrementCol = 1;
                break;
            case 3:  // left
                offsetCol = -1;
                incrementCol = -1;
                break;
        }

        while (Utils::onBoard(row + offsetRow, col + offsetCol)) {
            Piece* curPiece = g.getPiece(row + offsetRow, col + offsetCol);
            Pos pos = {row + offsetRow, col + offsetCol};

            if (curPiece != nullptr) {
                // can't jump over own piece
                if (curPiece->getColour() == this->getColour()) {
                    break;
                } else {
                    if (!check || !g.check(this, pos)) {
                        validMoves.push_back(pos);
                    }
                    break;
                }
            } else {  // empty spot
                if (!check || !g.check(this, pos)) {
                    validMoves.push_back(pos);
                }
            }
            offsetRow += incrementRow;
            offsetCol += incrementCol;
        }
    }

    return validMoves;
}

void Piece::MovePiece(int r, int c) {
    this->pos.row = r;
    this->pos.col = c;
}

void Piece::setPrev(Pos pos) {
    this->prev = pos;
}

Pos Piece::getPrev() {
    return this->prev;
}
