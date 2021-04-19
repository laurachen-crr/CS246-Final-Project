#ifndef UTILS_H
#define UTILS_H

#include "enums.h"

class Piece;

class Utils {
    public:
    static bool onBoard(int r, int c);
    static char pieceToChar(Piece* piece);
    static Type charToType(char c);
    static Colour charToColour(char c);
};

#endif
