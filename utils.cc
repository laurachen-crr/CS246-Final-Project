#include "utils.h"

#include "piece.h"

bool Utils::onBoard(int r, int c) {
    if (r < 8 && r >= 0 && c < 8 && c >=0) {
        return true;
    } else {
        return false;
    }
}

char Utils::pieceToChar(Piece* piece) {
    if (piece == nullptr) {
        return 'x';
    }
    Type type = piece->getType();
    Colour colour = piece->getColour();
    if (colour == Colour::White) {
        switch(type) {
            case Type::Bishop:
                return 'B';
            case Type::Queen:
                return 'Q';
            case Type::King:
                return 'K';
            case Type::Pawn:
                return 'P';
            case Type::Rook:
                return 'R';
            default:
                return 'N';
        }
    } else {
        switch(type) {
            case Type::Bishop:
                return 'b';
            case Type::Queen:
                return 'q';
            case Type::King:
                return 'k';
            case Type::Pawn:
                return 'p';
            case Type::Rook:
                return 'r';
            default:
                return 'n';
        }
    }
}

Type Utils::charToType(char c) {
    switch(c) {
        case 'r':
        case 'R':
            return Type::Rook;
        case 'K':
        case 'k':
            return Type::King;
        case 'p':
        case 'P':
            return Type::Pawn;
        case 'q':
        case 'Q':
            return Type::Queen;
        case 'b':
        case 'B':
            return Type::Bishop;
        default:
            return Type::Knight;
    }
}

Colour Utils::charToColour(char c) {
    if(c >= 'a' && c <= 'z') {
        return Colour::Black;
    } else {
        return Colour::White;
    }
}

