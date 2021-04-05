#include "observer.h"
#include "subject.h"

class Cell : public Subject<Info, State>, public Observer<Info, State> {
    const size_t r, c;
    Colour colour = Colour::NoColour;

    // Add other private members if necessary
    Direction getDir(Subject<Info, State> &whoFrom);
    bool opDir(Direction neighbor, Direction newPiece);
public:
    Cell(size_t r, size_t c);

    void setPiece(Colour colour); // Place a piece of given colour here.
    void toggle(); // Toggles my colour.

    void notify(Subject<Info, State> &whoFrom)
            override; // My neighbours will call this
    // when they've changed state
    Info getInfo() const override;
};
#endif
