#ifndef __STATE_H__
#define __STATE_H__

// on the board or off the board
enum class StateType { on, off };
// Optimal move: 
enum class OptimalMove { Random, Check, Capture}

struct State {
    StateType type; 
    OptimalMove move;

};

