#ifndef UTILS_H
#define UTILS_H

#include "enums.h"

class Piece;

class Utils {
    public:
    static char pieceToChar(Piece* piece);
    static Type charToType(char c);
    static Colour charToColour(char c);
    static Piece* createPiece(int row, int col, Colour colour, Type type);
};

#endif
