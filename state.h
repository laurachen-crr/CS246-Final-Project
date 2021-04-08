#ifndef __STATE_H__
#define __STATE_H__

// on the board or off the board
enum class StateType { On, Off };
// Optimal move: Still stands for not move
enum class OptimalMove { Still, Random, Check, Capture};

struct State {
    StateType type; 
    OptimalMove move;
};

#endif
