#include <iostream>
#include <string>

#include "cell.h"
#include "grid.h"
#include "observer.h"
#include "subject.h"
#include "utils.h"

using namespace std;

class InvalidCommand {};

int main(int nargs, char *args[]) {
    Grid g{};
    g.init();
    cout << g;
    Colour whoseMove = Colour::White;
    string command;
    char fromCol;
    int fromRow;
    char toCol;
    int toRow;
    string cmd;
    int seed = time(0);
    bool text = false;

    try {
        if (nargs > 4) {
            throw InvalidCommand();
        }

        for (int i = 1; i < nargs; ++i) {
            string arg = args[i];
            if (arg == "-text") {
                text = true;
            } else if (arg == "-seed") {
                cout << "seed" << endl;
                if (nargs == i + 1) {
                    throw InvalidCommand();
                } else {
                    seed = stoi(args[i + 1]);
                    cout << seed << endl;
                    ++i;
                }
            } else {
                throw InvalidCommand();
            }
        }
    } catch (...) {
        cout << "Invalid argument!" << endl;
        return 1;
    }

    while (cin >> command) {
        try {
            if (command == "game") {  // play mode
                string whiteplayer, blackplayer;
                cin >> whiteplayer >> blackplayer;

                int level;
                if (whiteplayer.substr(0, whiteplayer.size() - 1) ==
                    "computer") {
                    if (blackplayer != "human") {
                        throw InvalidCommand();
                    }
                    level = whiteplayer.back();
                    whiteplayer = "computer";
                } else if (blackplayer.substr(0, blackplayer.size() - 1) ==
                           "computer") {
                    if (whiteplayer != "human") {
                        throw InvalidCommand();
                    }
                    level = blackplayer.back();
                    blackplayer = "computer";
                } else if (whiteplayer != "human" || blackplayer != "human") {
                    throw InvalidCommand();
                }

                while (g.checkmate() == Result::InGame) {
                    try {
                        if (whoseMove == Colour::White) {
                            if (whiteplayer == "human") {
                                cin >> cmd;
                                if (cmd == "move") {
                                    cin >> fromCol >> fromRow >> toCol >> toRow;
                                    if (fromCol > 'h' || fromCol < 'a' ||
                                        toCol < 'a' || toCol > 'h') {
                                        throw InvalidCommand();
                                    } else if (fromRow < 1 || fromRow > 8 ||
                                               toRow < 1 || toRow > 8) {
                                        throw InvalidCommand();
                                    }
                                    // move the piece
                                    // g.move(whoseMove, fromRow-1, fromCol -
                                    // 'a', toRow-1, toCol - 'a'); cout << g <<
                                    // endl;
                                } else if (cmd == "resign") {
                                    cout << "White Resigned! Black Wins!"
                                         << endl;
                                    break;
                                } else {
                                    throw InvalidCommand();
                                }
                            } else if (whiteplayer == "computer") {
                                // make the computer move
                                // g.computerBestMove(whoseMove, level);
                                cout << "white computer made a move" << endl;
                            }
                        } else if (whoseMove == Colour::Black) {
                            if (blackplayer == "human") {
                                cin >> cmd;
                                if (cmd == "move") {
                                    cin >> fromCol >> fromRow >> toCol >> toRow;
                                    if (fromCol > 'h' || fromCol < 'a' ||
                                        toCol < 'a' || toCol > 'h') {
                                        throw InvalidCommand();
                                    } else if (fromRow < 1 || fromRow > 8 ||
                                               toRow < 1 || toRow > 8) {
                                        throw InvalidCommand();
                                    }
                                    // move the piece
                                    // g.move(whoseMove, fromRow-1, fromCol -
                                    // 'a', toRow-1, toCol - 'a'); cout << g <<
                                    // endl;
                                } else if (cmd == "resign") {
                                    cout << "Black resigned! White Wins!"
                                         << endl;
                                    break;
                                } else {
                                    throw InvalidCommand();
                                }
                            } else if (blackplayer == "computer") {
                                // make the computer move
                                // g.computerBestMove(whoseMove, level);
                                // cout << g << endl;
                            }
                        }

                        if (g.checkmate() == Result::WhiteWin) {
                            cout << "Checkmate! White Wins!" << endl;
                            break;
                        } else if (g.checkmate() == Result::BlackWin) {
                            cout << "Checkmate! Black Wins!" << endl;
                            break;
                        } else if (g.checkmate() == Result::Stalemate) {
                            cout << "Stalemate!" << endl;
                            break;
                        }
                        whoseMove = whoseMove == Colour::Black ? Colour::White
                                                               : Colour::Black;
                    } catch (InvalidCommand e) {
                        cout << "Invalid Command!" << endl;
                    }
                }
            } else if (command == "setup") {  // set up mode
                while (true) {
                    try {
                        cin >> cmd;
                        if (cmd == "+") {
                            char pieceName;
                            cin >> pieceName;
                            cin >> toCol;
                            cin >> toRow;
                            string s = "rnbqkpRNBQKP";
                            if (s.find(pieceName) == std::string::npos) {
                                throw InvalidCommand();
                            } else if (toCol < 'a' || toCol > 'h' ||
                                       toRow < 1 || toRow > 8) {
                                throw InvalidCommand();
                            } else {
                                if (g.setPiece(Utils::charToColour(pieceName),
                                               8 - toRow, toCol - 'a',
                                               Utils::charToType(pieceName))) {
                                    cout << g << endl;
                                } else {
                                    throw InvalidCommand();
                                }
                            }
                        } else if (cmd == "-") {
                            cin >> fromCol;
                            cin >> fromRow;
                            if (fromCol < 'a' || fromCol > 'h' || fromRow < 1 ||
                                fromRow > 8) {
                                throw InvalidCommand();
                            } else {
                                g.removePiece(8 - fromRow, fromCol - 'a');
                                cout << g << endl;
                            }
                        } else if (cmd == "=") {
                            string colour;
                            cin >> colour;
                            if (colour == "white") {
                                whoseMove = Colour::White;
                            } else if (colour == "black") {
                                whoseMove = Colour::Black;
                            } else {
                                throw InvalidCommand();
                            }
                        } else if (cmd == "done") {
                            break;
                        } else {
                            throw InvalidCommand();
                        }
                    } catch (InvalidCommand e) {
                        cout << "Invalid Command!" << endl;
                    }
                }
            } else if (command == "quit") {
                // quit the game
                break;
            } else {
                throw InvalidCommand();
            }
        } catch (InvalidCommand e) {
            cout << "Invalid Command!" << endl;
        }
    }
}
