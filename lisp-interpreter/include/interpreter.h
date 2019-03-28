#ifndef LISP_INTERPRETER_INTERPRETER_H
#define LISP_INTERPRETER_INTERPRETER_H

#include <string>
#include <vector>
#include "expressions.h"

class Interpreter {
private:
    Expression parse(std::vector<std::string> tokens);
    std::vector<std::string> tokenize(std::string string);
};

#endif
