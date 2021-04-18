#ifndef PIECE_H
#define PIECE_H
#include "observer.h"
#include "subject.h"
#include "grid.h"
#include "enums.h"

struct Pos {
    int row;
    int col;
};

class Piece : public Subject, public Observer {
    Type type;
    Pos pos;
    Colour colour;

public: 
    Piece(int row, int col, Colour colour, Type type);
    Type getType();
    Colour getColour();
    Pos getPos();
    void MovePiece(int r, int c); // Move a piece of given colour here.
    void notify(Subject &whoFrom) override; // My observers will call this when they've changed state
    virtual Pos findBestMove() = 0;
    virtual bool checkValidMove(int r, int c) = 0; // check if move to r, c is a valid move

};

class Queen : public Piece {
public:
    Queen(int row, int col, Colour);
    Pos findBestMove() override;
    bool checkValidMove(int r, int c) override;
};

class King : public Piece {
public:
    King(int row, int col, Colour);
    Pos findBestMove() override;
    bool checkValidMove(int r, int c) override;
};

class Pawn : public Piece {
    bool firstMove = true;
public:
    Pawn(int row, int col, Colour);
    Pos findBestMove() override;
    bool checkValidMove(int r, int c) override;
};

class Bishop : public Piece {
public:
    Bishop(int row, int col, Colour);
    Pos findBestMove() override;
    bool checkValidMove(int r, int c) override;

};

class Knight : public Piece {
public:
    Knight(int row, int col, Colour);
    Pos findBestMove() override;
    bool checkValidMove(int r, int c) override;
};

class Rook : public Piece {
public:
    Rook(int row, int col, Colour);
    Pos findBestMove() override;   
    bool checkValidMove(int r, int c) override;   
};

#endif

