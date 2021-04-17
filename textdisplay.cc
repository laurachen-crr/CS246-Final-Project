#include "textdisplay.h"
#include "utils.h"
#include "grid.h"

std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {
    for (int i = 0; i < 8; ++i) {
        std::cout << 8 - i << " ";
        for (int j = 0; j < 8; ++j) {
            std::cout << td.theDisplay.at(i).at(j);
        }
        std::cout << std::endl;
    }
    std::cout << "  abcdefgh" << endl;
    return out;
}

TextDisplay::TextDisplay() {
    this->theDisplay.resize(8);

    for (int i = 0; i < 4; ++i) {
        this->theDisplay.at(0).emplace_back('-');
        this->theDisplay.at(0).emplace_back(' ');
        this->theDisplay.at(2).emplace_back('-');
        this->theDisplay.at(2).emplace_back(' ');
        this->theDisplay.at(4).emplace_back('-');
        this->theDisplay.at(4).emplace_back(' ');
        this->theDisplay.at(6).emplace_back('-');
        this->theDisplay.at(6).emplace_back(' ');

        this->theDisplay.at(1).emplace_back(' ');
        this->theDisplay.at(1).emplace_back('-');
        this->theDisplay.at(3).emplace_back(' ');
        this->theDisplay.at(3).emplace_back('-');
        this->theDisplay.at(5).emplace_back(' ');
        this->theDisplay.at(5).emplace_back('-');
        this->theDisplay.at(7).emplace_back(' ');
        this->theDisplay.at(7).emplace_back('-');
    }

    this->emptyboard = this->theDisplay;
}

// void TextDisplay::init() {
//     this->theDisplay.at(0).at(0) = 'R';
//     this->theDisplay.at(0).at(1) = 'N';
//     this->theDisplay.at(0).at(2) = 'B';
//     this->theDisplay.at(0).at(3) = 'Q';
//     this->theDisplay.at(0).at(4) = 'K';
//     this->theDisplay.at(0).at(5) = 'B';
//     this->theDisplay.at(0).at(6) = 'N';
//     this->theDisplay.at(0).at(7) = 'R';

//     this->theDisplay.at(7).at(0) = 'r';
//     this->theDisplay.at(7).at(1) = 'n';
//     this->theDisplay.at(7).at(2) = 'b';
//     this->theDisplay.at(7).at(3) = 'q';
//     this->theDisplay.at(7).at(4) = 'k';
//     this->theDisplay.at(7).at(5) = 'b';
//     this->theDisplay.at(7).at(6) = 'n';
//     this->theDisplay.at(7).at(7) = 'r';

//     for (int i = 0; i < 8; ++i) {
//         this->theDisplay.at(1).at(i) = 'P';
//         this->theDisplay.at(6).at(i) = 'p';
//     }
// }

void TextDisplay::update(Grid &g) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            char pieceChar = Utils::pieceToChar(g.getPiece(i, j));
            if (pieceChar == 'x') {
                this->theDisplay.at(i).at(j) = this->emptyboard.at(i).at(j);
            } else {
                this->theDisplay.at(i).at(j) = pieceChar;
            }
        }
    }
}

TextDisplay::~TextDisplay() {}
