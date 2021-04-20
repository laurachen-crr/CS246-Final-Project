#include "computer.h"
#include "grid.h"
#include "enums.h"
#include "structs.h"
#include "utils.h"
#include "piece.h"
#include <utility>
#include <vector>
using namespace std;

Computer* Computer::createComputer(int level) {
    switch(level) {
        case 1:
            return new Computer1{};
            break;
        case 2:
            return new Computer2{};
            break;
        default:
            return new Computer3{};
    }
}

pair<Pos, Pos> Computer1::getNextMove(Grid& g, Colour colour) {
    vector<Piece*>& pieces = g.getPieces(colour);
    vector<pair<Pos, Pos>> allMoves;
    int size = 0;
    int index;

    // get random move
    for (auto piece : pieces) {
        vector<Pos> moves = piece->getValidMoves(g);
        for (auto pos : moves) {
            pair<Pos, Pos> p{piece->getPos(), pos};
            allMoves.emplace_back(p);
            size++;
        }
    }
    index = rand() % size;
    return allMoves.at(index);
}

pair<Pos, Pos> Computer2::getNextMove(Grid& g, Colour colour) {
    vector<Piece*>& pieces = g.getPieces(colour);
    vector<pair<Pos, Pos>> allMoves;
    int size = 0;
    int index;

    // get capture/check move
    vector<Piece*>& opponent = g.getPieces(Utils::opponent(colour));
    vector<Pos> opponentLocation;
    for (auto piece : opponent) {
        opponentLocation.emplace_back(piece->getPos());
    }

    Piece* king = g.findPiece(Type::King, Utils::opponent(colour));
    for (auto piece : pieces) {
        vector<Pos> moves = piece->getValidMoves(g);
        for (auto pos : moves) {

            // capture
            if (Utils::posInVector(opponentLocation, pos)) {
                pair<Pos, Pos> p{piece->getPos(), pos};
                allMoves.emplace_back(p);
                size++;
            }

            // check
            if (pos == king->getPos()) {
                pair<Pos, Pos> p{piece->getPos(), pos};
                allMoves.emplace_back(p);
                size++;
            }
        }
    }

    if (size > 0) {
        index = rand() % size;
        return allMoves.at(index);
    }

    // get random move 
    for (auto piece : pieces) {
        vector<Pos> moves = piece->getValidMoves(g);
        for (auto pos : moves) {
            pair<Pos, Pos> p{piece->getPos(), pos};
            allMoves.emplace_back(p);
            size++;
        }
    }
    index = rand() % size;
    return allMoves.at(index);
}

pair<Pos, Pos> Computer3::getNextMove(Grid& g, Colour colour) {
    vector<Piece*>& pieces = g.getPieces(colour);
    vector<pair<Pos, Pos>> allMoves;
    int size = 0;
    int index;

    // get capture/check/avoid move
    vector<Piece*>& opponent = g.getPieces(Utils::opponent(colour));
    vector<Pos> opponentLocation;
    vector<Pos> opponentMoves;

    for (auto piece : opponent) {
        opponentLocation.emplace_back(piece->getPos());
        vector<Pos> moves = piece->getValidMoves(g);
        for (auto pos : moves) {
            opponentMoves.emplace_back(pos);
        }
    }

    Piece* king = g.findPiece(Type::King, Utils::opponent(colour));
    for (auto piece : pieces) {
        vector<Pos> moves = piece->getValidMoves(g);
        bool avoid = Utils::posInVector(opponentMoves, piece->getPos());
        for (auto pos : moves) {

            // capture
            if (Utils::posInVector(opponentLocation, pos)) {
                pair<Pos, Pos> p{piece->getPos(), pos};
                allMoves.emplace_back(p);
                size++;
            }

            // check
            if (pos == king->getPos()) {
                pair<Pos, Pos> p{piece->getPos(), pos};
                allMoves.emplace_back(p);
                size++;
            }

            // avoid
            if (avoid && Utils::posInVector(opponentMoves, pos)) {
                pair<Pos, Pos> p{piece->getPos(), pos};
                allMoves.emplace_back(p);
                size++;
            }
        }
    }

    if (size > 0) {
        index = rand() % size;
        return allMoves.at(index);
    }

    // get random move 
    for (auto piece : pieces) {
        vector<Pos> moves = piece->getValidMoves(g);
        for (auto pos : moves) {
            pair<Pos, Pos> p{piece->getPos(), pos};
            allMoves.emplace_back(p);
            size++;
        }
    }
    index = rand() % size;
    return allMoves.at(index);
}

