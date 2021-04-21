#ifndef UTILS_H
#define UTILS_H
#include "enums.h"
#include "structs.h"
#include <vector>
using namespace std;

class Piece;

class Utils {
    public:
    static Colour opponent(Colour colour);
    static bool onBoard(int r, int c);
    static char pieceToChar(Piece* piece);
    static Type charToType(char c);
    static Colour charToColour(char c);

    template<typename T>
    static bool inVector(vector<T>& v, T value) {
        for (auto val : v) {
            if (val == value) {
                return true;
            }
        }
        return false;
    }
};

#endif
