#ifndef PIECE_H
#define PIECE_H
#include "observer.h"
#include "subject.h"
#include "info.h"
#include "state.h"

class Piece : public Subject<Info, State>, public Observer<Info, State> {
    Info myinfo;
    State mystate;


public:
    Piece(Info myinfo);

    void setPiece(Colour colour); // Place a piece of given colour here.

    void notify(Subject<Info, State> &whoFrom) override; // My observers will call this
    // when they've changed state
};

#endif
