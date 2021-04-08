#ifndef __INFO_H__
#define __INFO_H__
#include <cstddef>

enum class Type { King, Queen, Rook, Knight, Bishop, Pawn };
enum class Colour { Black, White };

struct Info {
    int row;
    int col;
    Type pieceName;
    Colour colour;
};

#endif
