#ifndef LISP_INTERPRETER_INTERPRETER_H
#define LISP_INTERPRETER_INTERPRETER_H

#include <string>
#include <vector>
#include "parser.h"

class Interpreter {
private:
    Parser parser;
public:
    Interpreter(Parser p) : parser(p) {}

    std::shared_ptr<EvaluatedExpression> eval(const std::string& string) {
        return parser.parse(string)->eval();
    }
};

#endif
