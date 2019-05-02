#ifndef LISP_INTERPRETER_PARSE_H
#define LISP_INTERPRETER_PARSE_H

#include <string>
#include <vector>
#include "expression.h"
#include "parse_error.h"

class Parser {
private:
    Expression parse(const std::vector<std::string> &tokens) const;
public:
    inline Expression parse(const std::string &string) const {
        return parse(tokenize(string));
    }

    std::vector<std::string> tokenize(const std::string &string) const;
};

#endif
