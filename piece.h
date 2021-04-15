#ifndef PIECE_H
#define PIECE_H
#include "observer.h"
#include "subject.h"

enum class Type { King, Queen, Rook, Knight, Bishop, Pawn };
enum class Colour { Black, White };

struct Pos {
    int row;
    int col;
};

class Piece : public Subject, public Observer {
    Type type;
    Pos pos;
    Colour colour;
    virtual bool checkValidMove(int r, int c) = 0; // check if move to r, c is a valid move

public: 
    Piece(int row, int col, Colour colour, Type type);
    Type getType();
    void MovePiece(int r, int c); // Move a piece of given colour here.
    void notify(Subject &whoFrom) override; // My observers will call this when they've changed state
    virtual Pos findBestMove() = 0;
};

class Queen : public Piece {
    bool checkValidMove(int r, int c) override;
public:
    Queen(int row, int col, Colour);
    Pos findBestMove() override;
};

class King : public Piece {
    bool checkValidMove(int r, int c) override;
public:
    King(int row, int col, Colour);
    Pos findBestMove() override;
};

class Pawn : public Piece {
    bool checkValidMove(int r, int c) override;
public:
    Pawn(int row, int col, Colour);
    Pos findBestMove() override;
};

class Bishop : public Piece {
    bool checkValidMove(int r, int c) override;
public:
    Bishop(int row, int col, Colour);
    Pos findBestMove() override;
};

class Knight : public Piece {
    bool checkValidMove(int r, int c) override;
public:
    Knight(int row, int col, Colour);
    Pos findBestMove() override;
};

class Rook : public Piece {
    bool checkValidMove(int r, int c) override;
public:
    Rook(int row, int col, Colour);
    Pos findBestMove() override;             
};

#endif

