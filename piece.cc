#include "piece.h"

Piece::Piece(Info myinfo) {
    this->myinfo = myinfo;
    this->mystate = { StateType::On, OptimalMove::Still };
}