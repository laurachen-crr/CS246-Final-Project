#ifndef STRUCTS_H
#define STRUCTS_H

struct Pos {
    int row;
    int col;

    bool operator==(const Pos& rhs) const {
        return (this->row == rhs.row && this->col == rhs.col);
    }
};

#endif
