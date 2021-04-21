#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <string>
using namespace std;

class InvalidCommand {
    public:
    string msg;
    InvalidCommand(string msg) {
        this->msg = msg;
    }
};

#endif
