#include <stdlib.h>

#include <iostream>
#include <sstream>
#include <string>

#include "cell.h"
#include "computer.h"
#include "exception.h"
#include "grid.h"
#include "utils.h"

using namespace std;

int main(int nargs, char* args[]) {
    Colour whoseMove = Colour::White;
    string command;
    char fromCol;
    int fromRow;
    char toCol;
    int toRow;
    string cmd;
    int seed = time(0);
    bool text = false;
    bool setup = false;
    string residual;
    string validPieces = "rnbqkpRNBQKP";
    string whitePieces = "RNBQKP";
    string blackPieces = "rnbqkp";
    string line;
    char promotion = ' ';
    double whiteScore = 0;
    double blackScore = 0;

    try {
        if (nargs > 4) {
            throw InvalidCommand(
                "The number of arguments should be no more than 4!");
        }

        for (int i = 1; i < nargs; ++i) {
            string arg = args[i];
            if (arg == "-text") {
                text = true;
            } else if (arg == "-seed") {
                cout << "seed" << endl;
                if (nargs == i + 1) {
                    throw InvalidCommand("Invalid argument!");
                } else {
                    seed = stoi(args[i + 1]);
                    cout << seed << endl;
                    ++i;
                }
            } else {
                throw InvalidCommand("Invalid argument!");
            }
        }
    } catch (InvalidCommand e) {
        cout << e.msg << endl;
        return 1;
    }
    Grid g{text};
    while (getline(cin, line)) {
        istringstream iss(line);
        try {
            iss >> command;
            if (command == "game") {  // play mode
                string whiteplayer, blackplayer;
                iss >> whiteplayer >> blackplayer;
                if (!setup) {
                    g.init();
                }
                int level = -1;
                Computer* computer = nullptr;
                if (whiteplayer.substr(0, whiteplayer.size() - 1) ==
                    "computer") {
                    if (blackplayer != "human") {
                        throw InvalidCommand("Invalid game argument!");
                    }
                    level = whiteplayer.back() - '0';
                    whiteplayer = "computer";
                } else if (blackplayer.substr(0, blackplayer.size() - 1) ==
                           "computer") {
                    if (whiteplayer != "human") {
                        throw InvalidCommand("Invalid game argument!");
                    }
                    level = blackplayer.back() - '0';
                    blackplayer = "computer";
                } else if (whiteplayer != "human" || blackplayer != "human") {
                    throw InvalidCommand("Invalid game argument!");
                }

                if (!(level == -1 || level == 1 || level == 2 || level == 3)) {
                    throw InvalidCommand("We only support level 1, 2, 3!");
                }

                if (level != -1) {
                    srand(seed);
                    computer = Computer::createComputer(level);
                }
                cout << g << endl;

                while (g.checkmate() == Result::InGame) {
                    try {
                        if (whoseMove == Colour::White) {
                            if (whiteplayer == "human") {
                                getline(cin, line);
                                istringstream iss(line);
                                iss >> cmd;
                                if (cmd == "move") {
                                    iss >> fromCol >> fromRow >> toCol >> toRow;

                                    if (!iss.eof()) {
                                        iss >> residual;
                                        if (residual.length() == 1) {
                                            promotion = residual[0];
                                            if (whitePieces.find(promotion) ==
                                                std::string::npos) {
                                                throw InvalidCommand(
                                                    "Invalid promotion type!");
                                            }
                                        } else {
                                            throw InvalidCommand(
                                                "Invalid command!");
                                        }
                                    }
                                    // move the piece
                                    if (!(g.move(
                                            whoseMove, 8 - fromRow,
                                            fromCol - 'a', 8 - toRow,
                                            toCol - 'a',
                                            Utils::charToType(promotion)))) {
                                        throw InvalidCommand(
                                            "White invalid move!");
                                    }
                                    cout << g << endl;
                                } else if (cmd == "resign") {
                                    blackScore += 1;
                                    cout << "White Resigned! Black Wins!"
                                         << endl;
                                    delete computer;
                                    break;
                                } else {
                                    throw InvalidCommand("Invalid command!");
                                }
                            } else if (whiteplayer == "computer") {
                                // make the computer move
                                std::pair<Pos, Pos> move =
                                    computer->getNextMove(g, Colour::White);
                                g.move(Colour::White, move.first.row,
                                       move.first.col, move.second.row,
                                       move.second.col);
                                cout << g << endl;
                            }
                        } else if (whoseMove == Colour::Black) {
                            if (blackplayer == "human") {
                                getline(cin, line);
                                istringstream iss(line);
                                iss >> cmd;
                                if (cmd == "move") {
                                    iss >> fromCol >> fromRow >> toCol >> toRow;
                                    // move the piece
                                    if (!(g.move(whoseMove, 8 - fromRow,
                                                 fromCol - 'a', 8 - toRow,
                                                 toCol - 'a'))) {
                                        throw InvalidCommand{
                                            "Black invalid move!"};
                                    }
                                    cout << g << endl;
                                } else if (cmd == "resign") {
                                    whiteScore += 1;
                                    cout << "Black resigned! White Wins!"
                                         << endl;
                                    delete computer;
                                    break;
                                } else {
                                    throw InvalidCommand("Invalid command!");
                                }
                            } else if (blackplayer == "computer") {
                                std::pair<Pos, Pos> move =
                                    computer->getNextMove(g, Colour::Black);
                                g.move(Colour::Black, move.first.row,
                                       move.first.col, move.second.row,
                                       move.second.col);
                                cout << g << endl;
                            }
                        }
                        Result result = g.checkmate();
                        if(!(result == Result::InGame)) {
                            delete computer;
                            if (result == Result::WhiteWin) {
                                whiteScore += 1;
                                cout << "Checkmate! White Wins!" << endl;
                                break;
                            } else if (result == Result::BlackWin) {
                                blackScore += 1;
                                cout << "Checkmate! Black Wins!" << endl;
                                break;
                            } else if (result == Result::Stalemate) {
                                blackScore += 0.5;
                                whiteScore += 0.5;
                                cout << "Stalemate!" << endl;
                                break;
                            }
                        }
                        
                        whoseMove = whoseMove == Colour::Black ? Colour::White
                                                               : Colour::Black;
                    } catch (InvalidCommand e) {
                        cout << e.msg << endl;
                    }
                }
                setup = false;
            } else if (command == "setup") {  // set up mode
                g.init(true);
                setup = true;
                cout << g << endl;
                while (true) {
                    getline(cin, line);
                    istringstream iss(line);
                    try {
                        iss >> cmd;
                        if (cmd == "+") {
                            char pieceName;
                            iss >> pieceName;
                            iss >> toCol;
                            iss >> toRow;
                            if (validPieces.find(pieceName) ==
                                std::string::npos) {
                                throw InvalidCommand("Invalid piece name!");
                            } else if (toCol < 'a' || toCol > 'h' ||
                                       toRow < 1 || toRow > 8) {
                                throw InvalidCommand("Invalid move!");
                            } else {
                                g.setupSetPiece(Utils::charToColour(pieceName),
                                           8 - toRow, toCol - 'a',
                                           Utils::charToType(pieceName));
                                cout << g << endl;
                            }
                        } else if (cmd == "-") {
                            iss >> fromCol;
                            iss >> fromRow;
                            if (fromCol < 'a' || fromCol > 'h' || fromRow < 1 ||
                                fromRow > 8) {
                                throw InvalidCommand("Invalid move!");
                            } else {
                                g.setupRemovePiece(8 - fromRow, fromCol - 'a');
                                cout << g << endl;
                            }
                        } else if (cmd == "=") {
                            string colour;
                            iss >> colour;
                            if (colour == "white") {
                                whoseMove = Colour::White;
                            } else if (colour == "black") {
                                whoseMove = Colour::Black;
                            } else {
                                throw InvalidCommand("Invalid colour!");
                            }
                        } else if (cmd == "done") {
                            if (g.validateSetup()) {
                                break;
                            } else {
                                throw InvalidCommand("Invalid board setup!");
                            }
                        } else {
                            throw InvalidCommand("Invalid command!");
                        }
                    } catch (InvalidCommand e) {
                        cout << e.msg << endl;
                    }
                }
            } else if (command == "quit") {
                // quit the game
                break;
            } else {
                throw InvalidCommand("Invalid command!");
            }
        } catch (InvalidCommand e) {
            cout << e.msg << endl;
        }
    }
    cout << "Final Score:" << endl;
    cout << "White: " << whiteScore << endl;
    cout << "Black: " << blackScore << endl;
}
