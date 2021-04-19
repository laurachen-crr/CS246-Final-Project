#include "piece.h"
#include "grid.h"
#include "utils.h"
#include <vector>
using namespace std;

// helper for rook 
int validMove(Grid& g, int atR, int atC, Colour colour) {
    Piece* currPiece = g.getPiece(atR, atC);
    if (currPiece == nullptr) { // no piece at cell
        return 0; // legal move
    } else {
        Colour currColour = currPiece->getColour(); // get colour of piece at cell atR, atC
        if (colour == currColour) {  // colour of atR,atC is the same as piece in question
            return 1; // illegal
        } else {
            return 2; // legal but stop here
        }
    }
}

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

bool King::checkValidMove(int r, int c, Grid& g) { 
    Pos destination = {r, c};
    vector<Pos> allValidMoves = this->getValidMoves(g);
    return Utils::posInVector(allValidMoves, destination);
}

bool Queen::checkValidMove(int r, int c, Grid& g) { 
    Pos destination = {r, c};
    vector<Pos> allValidMoves = this->getValidMoves(g);
    return Utils::posInVector(allValidMoves, destination); 
}

bool Bishop::checkValidMove(int r, int c, Grid& g) {
    Pos destination = {r, c};
    vector<Pos> allValidMoves = this->getValidMoves(g);
    return Utils::posInVector(allValidMoves, destination);
}

bool Pawn::checkValidMove(int r, int c, Grid& g) {
    Pos destination = {r, c};
    vector<Pos> allValidMoves = this->getValidMoves(g);
    return Utils::posInVector(allValidMoves, destination);
}

bool Rook::checkValidMove(int r, int c, Grid& g) {
    Pos destination = {r, c};
    vector<Pos> allValidMoves = this->getValidMoves(g);
    return Utils::posInVector(allValidMoves, destination);
}

bool Knight::checkValidMove(int r, int c, Grid& g) {
    Pos destination = {r, c};
    vector<Pos> allValidMoves = this->getValidMoves(g);
    return Utils::posInVector(allValidMoves, destination);
}

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
                    if (g.check(this,pos) != colour) {
                        allValidMoves.emplace_back(pos);
                    }
                }
            }
        }
    }
    return allValidMoves;
}

vector<Pos> Queen::getValidMoves(Grid& g) {
    vector<Pos> validMoves;
    int currR = this->getPos().row;
    int currC = this->getPos().col;
    Colour colour = this->getColour();

    // find top right diag
    int tempR = currR + 1;
    int tempC = currC + 1;
    while (tempC <= 7 && tempR <= 7) {
        int moveStatus = validMove(g, tempR, tempC, colour);
        if (moveStatus == 0) {
            if (g.check(this, Pos{tempR, tempC}) != colour) {
                validMoves.push_back(Pos{tempR, tempC});
            } else {
                continue;
            }
        } else if (moveStatus == 1) {
            break;
        } else {
            if (g.check(this, Pos{tempR, tempC}) != colour) {
                validMoves.push_back(Pos{tempR, tempC});
            }
            break;
        }
        tempR += 1;
        tempC += 1;
    }

    // find bottom right diag
    tempR = currR - 1;
    tempC = currC + 1;
    while (tempC <= 7 && tempR >= 0) {
        int moveStatus = validMove(g, tempR, tempC, colour);
        if (moveStatus == 0) {
            if (g.check(this, Pos{tempR, tempC}) != colour) {
                validMoves.push_back(Pos{tempR, tempC});
            } else {
                continue;
            }
        } else if (moveStatus == 1) {
            break;
        } else {
            if (g.check(this, Pos{tempR, tempC}) != colour) {
                validMoves.push_back(Pos{tempR, tempC});
            }
            break;
        }
        tempR -= 1;
        tempC += 1;
    }

    // find bottom left diag
    tempR = currR - 1;
    tempC = currC - 1;
    while (tempC >= 0 && tempR >= 0) {
       int moveStatus = validMove(g, tempR, tempC, colour);
        if (moveStatus == 0) {
            if (g.check(this, Pos{tempR, tempC}) != colour) {
                validMoves.push_back(Pos{tempR, tempC});
            } else {
                continue;
            }
        } else if (moveStatus == 1) {
            break;
        } else {
            if (g.check(this, Pos{tempR, tempC}) != colour) {
                validMoves.push_back(Pos{tempR, tempC});
            }
            break;
        }
        tempR -= 1;
        tempC -= 1;
    }

    // find top left diag
    tempR = currR + 1;
    tempC = currC - 1;
    while (tempC >= 0 && tempR <= 7) {
        int moveStatus = validMove(g, tempR, tempC, colour);
        if (moveStatus == 0) {
            if (g.check(this, Pos{tempR, tempC}) != colour) {
                validMoves.push_back(Pos{tempR, tempC});
            } else {
                continue;
            }
        } else if (moveStatus == 1) {
            break;
        } else {
            if (g.check(this, Pos{tempR, tempC}) != colour) {
                validMoves.push_back(Pos{tempR, tempC});
            }
            break;
        }
        tempR += 1;
        tempC -= 1;
    }

    tempR = currR + 1;
    // find moves forward
    while (tempR <= 7) {
        int moveStatus = validMove(g, tempR, currC, colour);
        if (moveStatus == 0) {
            if (g.check(this,Pos{tempR, currC}) != colour) {
                validMoves.push_back(Pos{tempR, currC});
            } else {
                continue;
            }
        } else if (moveStatus == 1) {
            break;
        } else {
            if (g.check(this,Pos{tempR, currC}) != colour) {
                validMoves.push_back(Pos{tempR, currC});
            }
            break;
        }
        tempR += 1;
    }

    tempR = currR - 1;
    // find moves backward
    while (tempR >= 0) {
        int moveStatus = validMove(g, tempR, currC, colour);
        if (moveStatus == 0) {
            if (g.check(this,Pos{tempR, currC}) != colour) {
                validMoves.push_back(Pos{tempR, currC});
            } else {
                continue;
            }
        } else if (moveStatus == 1) {
            break;
        } else {
            if (g.check(this,Pos{tempR, currC}) != colour) {
                validMoves.push_back(Pos{tempR, currC});
            }
            break;
        }
        tempR -= 1;
    }

    tempC = currC + 1;
    // find moves to the right
    while (tempC <= 7) {
        int moveStatus = validMove(g, currR, tempC, colour);
        if (moveStatus == 0) {
            if (g.check(this,Pos{currR,tempC}) != colour) {
                validMoves.push_back(Pos{currR, tempC});
            } else {
                continue;
            }
        } else if (moveStatus == 1) {
            break;
        } else {
            if (g.check(this, Pos{currR,tempC}) != colour) {
                validMoves.push_back(Pos{currR, tempC});
            }
            break;
        }
        tempC += 1;
    }

    tempC = currC - 1;
    // find moves to the left
    while (tempC >= 0) {
        int moveStatus = validMove(g, currR, tempC, colour);
        if (moveStatus == 0) {
            if (g.check(this,Pos{currR,tempC}) != colour) {
                validMoves.push_back(Pos{currR, tempC});
            } else {
                continue;
            }
        } else if (moveStatus == 1) {
            break;
        } else {
            if (g.check(this, Pos{currR,tempC}) != colour) {
                validMoves.push_back(Pos{currR, tempC});
            }
            break;
        }
        tempC -= 1;
    }
    return validMoves;
}

vector<Pos> Bishop::getValidMoves(Grid& g) {
    vector<Pos> validMoves;
    int currR = this->getPos().row;
    int currC = this->getPos().col;
    Colour colour = this->getColour();

    // find top right diag
    int tempR = currR + 1;
    int tempC = currC + 1;
    while (tempC <= 7 && tempR <= 7) {
        int moveStatus = validMove(g, tempR, tempC, colour);
        if (moveStatus == 0) {
            if (g.check(this, Pos{tempR, tempC}) != colour) {
                validMoves.push_back(Pos{tempR, tempC});
            } else {
                continue;
            }
        } else if (moveStatus == 1) {
            break;
        } else {
            if (g.check(this, Pos{tempR, tempC}) != colour) {
                validMoves.push_back(Pos{tempR, tempC});
            }
            break;
        }
        tempR += 1;
        tempC += 1;
    }

    // find bottom right diag
    tempR = currR - 1;
    tempC = currC + 1;
    while (tempC <= 7 && tempR >= 0) {
        int moveStatus = validMove(g, tempR, tempC, colour);
        if (moveStatus == 0) {
            if (g.check(this, Pos{tempR, tempC}) != colour) {
                validMoves.push_back(Pos{tempR, tempC});
            } else {
                continue;
            }
        } else if (moveStatus == 1) {
            break;
        } else {
            if (g.check(this, Pos{tempR, tempC}) != colour) {
                validMoves.push_back(Pos{tempR, tempC});
            }
            break;
        }
        tempR -= 1;
        tempC += 1;
    }

    // find bottom left diag
    tempR = currR - 1;
    tempC = currC - 1;
    while (tempC >= 0 && tempR >= 0) {
       int moveStatus = validMove(g, tempR, tempC, colour);
        if (moveStatus == 0) {
            if (g.check(this, Pos{tempR, tempC}) != colour) {
                validMoves.push_back(Pos{tempR, tempC});
            } else {
                continue;
            }
        } else if (moveStatus == 1) {
            break;
        } else {
            if (g.check(this, Pos{tempR, tempC}) != colour) {
                validMoves.push_back(Pos{tempR, tempC});
            }
            break;
        }
        tempR -= 1;
        tempC -= 1;
    }

    // find top left diag
    tempR = currR + 1;
    tempC = currC - 1;
    while (tempC >= 0 && tempR <= 7) {
        int moveStatus = validMove(g, tempR, tempC, colour);
        if (moveStatus == 0) {
            if (g.check(this, Pos{tempR, tempC}) != colour) {
                validMoves.push_back(Pos{tempR, tempC});
            } else {
                continue;
            }
        } else if (moveStatus == 1) {
            break;
        } else {
            if (g.check(this, Pos{tempR, tempC}) != colour) {
                validMoves.push_back(Pos{tempR, tempC});
            }
            break;
        }
        tempR += 1;
        tempC -= 1;
    }
    return validMoves;

}

vector<Pos> Pawn::getValidMoves(Grid& g) {
    int row = this->getPos().row;
    int col = this->getPos().col;
    Colour colour = this->getColour();
    vector<Pos> allValidMoves;

    if(this->getColour() == Colour::White) {
        if(row != 0) {
            if(g.getPiece(row-1, col) == nullptr) {
                if (g.check(this, Pos{row-1,col}) != colour) {
                    allValidMoves.push_back({row-1, col});
                }
            }

            if(Utils::onBoard(row-1, col+1)) {
                if(g.getPiece(row-1, col+1) != nullptr && g.getPiece(row-1, col+1)->getColour() == Colour::Black) {
                    if (g.check(this, Pos{row-1,col+1}) != colour) {
                        allValidMoves.push_back({row-1, col+1});
                    }
                }
            } else if(Utils::onBoard(row-1, col-1)) {
                if(g.getPiece(row-1, col-1) != nullptr && g.getPiece(row-1, col-1)->getColour() == Colour::Black) {
                    if (g.check(this, Pos{row-1,col-1}) != colour) {
                        allValidMoves.push_back({row-1, col-1});
                    }
                }
            }
            if(row == 6) {
                if(g.getPiece(4, col) == nullptr) {
                    if (g.check(this, Pos{4,col}) != colour) {
                        allValidMoves.push_back({4, col});
                    }
                } 
            }
        }
    } else {
        if(row != 7) {
            if(g.getPiece(row+1, col) == nullptr) {
                if (g.check(this, Pos{row+1,col}) != colour) {
                    allValidMoves.push_back({row+1, col});
                }
            }
            
            if(Utils::onBoard(row+1, col+1)) {
                if(g.getPiece(row+1, col+1) != nullptr && g.getPiece(row+1, col+1)->getColour() == Colour::White) {
                    if (g.check(this, Pos{row+1,col+1}) != colour) {
                        allValidMoves.push_back({row+1, col+1});
                    }
                }
            } else if(Utils::onBoard(row+1, col-1)) {
                if(g.getPiece(row+1, col-1) != nullptr && g.getPiece(row+1, col-1)->getColour() == Colour::White) {
                    if (g.check(this, Pos{row+1,col-1}) != colour) {
                        allValidMoves.push_back({row+1, col-1});
                    }
                }
            }
            if(row == 1) {
                if(g.getPiece(3, col) == nullptr) {
                    if (g.check(this, Pos{3,col}) != colour) {
                        allValidMoves.push_back({3, col});
                    }
                }
                
            }
        }
    }
    return allValidMoves;
}

vector<Pos> Knight::getValidMoves(Grid& g) { // STILL HAVE TO ADD CHECK IN THIS
    int row = this->getPos().row;
    int col = this->getPos().col;
    Colour colour = this->getColour();
    vector<Pos> allValidMoves;

    if(Utils::onBoard(row+2, col+1)) {
        allValidMoves.push_back({row+2, col+1});
        if(g.getPiece(row+2, col+1) != nullptr && g.getPiece(row+2, col+1)->getColour() == this->getColour()) {
            allValidMoves.pop_back();
        } else if (g.check(this, Pos{row+2,col+1}) != colour) {
            allValidMoves.pop_back();
        }
    } else if(Utils::onBoard(row-2, col+1)) {
        allValidMoves.push_back({row-2, col+1});
        if(g.getPiece(row-2, col+1) != nullptr && g.getPiece(row-2, col+1)->getColour() == this->getColour()) {
            allValidMoves.pop_back();
        } else if (g.check(this, Pos{row-2,col+1}) != colour) {
            allValidMoves.pop_back();
        }
    } else if(Utils::onBoard(row+2, col-1)) {
        allValidMoves.push_back({row+2, col-1});
        if(g.getPiece(row+2, col-1) != nullptr && g.getPiece(row+2, col-1)->getColour() == this->getColour()) {
            allValidMoves.pop_back();
        } else if (g.check(this, Pos{row+2,col-1}) != colour) {
            allValidMoves.pop_back();
        }
    } else if(Utils::onBoard(row-2, col-1)) {
        allValidMoves.push_back({row-2, col-1});
        if(g.getPiece(row-2, col-1) != nullptr && g.getPiece(row-2, col-1)->getColour() == this->getColour()) {
            allValidMoves.pop_back();
        } else if (g.check(this, Pos{row-2,col-1}) != colour) {
            allValidMoves.pop_back();
        }
    }
    return allValidMoves;
}

vector<Pos> Rook::getValidMoves(Grid& g) {
    vector<Pos> validMoves;
    int currR = this->getPos().row;
    int currC = this->getPos().col;
    Colour colour = this->getColour();

    int tempR = currR + 1;
    // find moves forward
    while (tempR <= 7) {
        int moveStatus = validMove(g, tempR, currC, colour);
        if (moveStatus == 0) {
            if (g.check(this,Pos{tempR, currC}) != colour) {
                validMoves.push_back(Pos{tempR, currC});
            } else {
                continue;
            }
        } else if (moveStatus == 1) {
            break;
        } else {
            if (g.check(this,Pos{tempR, currC}) != colour) {
                validMoves.push_back(Pos{tempR, currC});
            }
            break;
        }
        tempR += 1;
    }

    tempR = currR - 1;
    // find moves backward
    while (tempR >= 0) {
        int moveStatus = validMove(g, tempR, currC, colour);
        if (moveStatus == 0) {
            if (g.check(this,Pos{tempR, currC}) != colour) {
                validMoves.push_back(Pos{tempR, currC});
            } else {
                continue;
            }
        } else if (moveStatus == 1) {
            break;
        } else {
            if (g.check(this,Pos{tempR, currC}) != colour) {
                validMoves.push_back(Pos{tempR, currC});
            }
            break;
        }
        tempR -= 1;
    }

    int tempC = currC + 1;
    // find moves to the right
    while (tempC <= 7) {
        int moveStatus = validMove(g, currR, tempC, colour);
        if (moveStatus == 0) {
            if (g.check(this,Pos{currR,tempC}) != colour) {
                validMoves.push_back(Pos{currR, tempC});
            } else {
                continue;
            }
        } else if (moveStatus == 1) {
            break;
        } else {
            if (g.check(this, Pos{currR,tempC}) != colour) {
                validMoves.push_back(Pos{currR, tempC});
            }
            break;
        }
        tempC += 1;
    }

    tempC = currC - 1;
    // find moves to the left
    while (tempC >= 0) {
        int moveStatus = validMove(g, currR, tempC, colour);
        if (moveStatus == 0) {
            if (g.check(this,Pos{currR,tempC}) != colour) {
                validMoves.push_back(Pos{currR, tempC});
            } else {
                continue;
            }
        } else if (moveStatus == 1) {
            break;
        } else {
            if (g.check(this, Pos{currR,tempC}) != colour) {
                validMoves.push_back(Pos{currR, tempC});
            }
            break;
        }
        tempC -= 1;
    }
    return validMoves;
}

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
