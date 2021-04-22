#ifndef PIECE_H
#define PIECE_H
#include "enums.h"
#include "structs.h"
#include <vector>
using namespace std;

class Grid;

class Piece {
    Type type;
    Pos pos;
    Colour colour;
    Pos prev;

public: 
    Piece(int row, int col, Colour colour, Type type);
    virtual ~Piece();
    static Piece* createPiece(int row, int col, Colour colour, Type type);
    Type getType();
    Colour getColour();
    Pos getPos();
    Pos getPrev();
    void setPrev(Pos pos);
    void setPos(int r, int c);
    void MovePiece(int r, int c); // Move a piece of given colour here.
    virtual bool checkValidMove(int r, int c, Grid& g) = 0; // check if move to r, c is a valid move
    virtual vector<Pos> getValidMoves(Grid& g, bool check = true) = 0;
};

class Queen : public Piece {
public:
    Queen(int row, int col, Colour);
    bool checkValidMove(int r, int c, Grid& g) override;
    vector<Pos> getValidMoves(Grid& g, bool check = true) override;
};

class King : public Piece {
public:
    King(int row, int col, Colour);
    bool checkValidMove(int r, int c, Grid& g) override;
    vector<Pos> getValidMoves(Grid& g, bool check = true) override;
};

class Pawn : public Piece {
public:
    Pawn(int row, int col, Colour);
    bool checkValidMove(int r, int c, Grid& g) override;
    vector<Pos> getValidMoves(Grid& g, bool check = true) override;
};

class Bishop : public Piece {
public:
    Bishop(int row, int col, Colour);
    bool checkValidMove(int r, int c, Grid& g) override;
    vector<Pos> getValidMoves(Grid& g, bool check = true) override;
};

class Knight : public Piece {
public:
    Knight(int row, int col, Colour);
    bool checkValidMove(int r, int c, Grid& g) override;
    vector<Pos> getValidMoves(Grid& g, bool check = true) override;
};

class Rook : public Piece {
public:
    Rook(int row, int col, Colour);
    bool checkValidMove(int r, int c, Grid& g) override;   
    vector<Pos> getValidMoves(Grid& g, bool check = true) override;
};

#endif

