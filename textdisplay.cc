#include "textdisplay.h"

std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {
    for (int i = 7; i >= 0; --i) {
        cout << i + 1 << " ";
        for (int j = 0; i < 8; ++j) {
            cout << td.theDisplay.at(i).at(j);
        }
        cout << endl;
    }
    cout << "abcdefgh" << endl;
    return out;
}

TextDisplay::TextDisplay() {
    this->theDisplay.resize(8);
    for (int i = 0; i < 8; ++i) {
        this->theDisplay.at(i).resize(8);
    }
}

void TextDisplay::init() {
    this->theDisplay.at(0).emplace_back('R');
    this->theDisplay.at(0).emplace_back('N');
    this->theDisplay.at(0).emplace_back('B');
    this->theDisplay.at(0).emplace_back('Q');
    this->theDisplay.at(0).emplace_back('K');
    this->theDisplay.at(0).emplace_back('B');
    this->theDisplay.at(0).emplace_back('N');
    this->theDisplay.at(0).emplace_back('R');

    this->theDisplay.at(7).emplace_back('r');
    this->theDisplay.at(7).emplace_back('n');
    this->theDisplay.at(7).emplace_back('b');
    this->theDisplay.at(7).emplace_back('q');
    this->theDisplay.at(7).emplace_back('k');
    this->theDisplay.at(7).emplace_back('b');
    this->theDisplay.at(7).emplace_back('n');
    this->theDisplay.at(7).emplace_back('r');

    for(int i = 0; i < 8; ++i) {
        this->theDisplay.at(1).emplace_back('P');
        this->theDisplay.at(6).emplace_back('p');
    }

    for(int i = 0; i < 4; ++i) {
        this->theDisplay.at(3).emplace_back('-');
        this->theDisplay.at(3).emplace_back(' ');
        this->theDisplay.at(4).emplace_back(' ');
        this->theDisplay.at(4).emplace_back('-');
    }

    this->theDisplay.at(5) = this->theDisplay.at(3);
    this->theDisplay.at(6) = this->theDisplay.at(4);
}

void TextDisplay::notify(Subject &board) {

}

TextDisplay::~TextDisplay() {
    
}
