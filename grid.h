#ifndef GRID_H
#define GRID_H
#include <iostream>
#include <vector>
#include "cell.h"
#include "piece.h"
#include "subject.h"
#include "enums.h"

class InvalidMove {};
class TextDisplay;

class Grid : public Subject, public Observer {
    std::vector<std::vector<Cell>> grid;
    std::vector<Piece *> black;
    std::vector<Piece *> white;

    TextDisplay *td;  // The text display.
    // GraphDisplay *gd = nullptr; // Another observer (intent:  graphics)
    void setObserver(Observer *ob);

   public:
    Grid();
    ~Grid();
    void init();
    bool move(Colour colour, int fromR, int fromC, int toR, int toC);  // move pieceName to toR, toC
    void computerBestMove();
    bool setPiece(Colour colour, int r, int c, Type type);
    void setPiece(int r, int c, Piece* newPiece);
    Piece* findPiece(Type type, Colour colour);
    bool check();        // check whether one side is checked
    void removePiece(Piece* piece);
    void removePiece(int r, int c);
    Result checkmate();  // check whether the game is over
    friend std::ostream &operator<<(std::ostream &out, const Grid &g);
    void notify(Subject &whoFrom) override;
    // piece: rnbqkpRNBQKP
    Piece* getPiece(int r, int c);  // returns nullptr is there is no piece on it
};

#endif
