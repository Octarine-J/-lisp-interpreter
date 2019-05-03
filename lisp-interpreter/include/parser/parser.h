#ifndef LISP_INTERPRETER_PARSE_H
#define LISP_INTERPRETER_PARSE_H

#include "expression.h"
#include "parse_error.h"
#include "tokenizer.h"

class Parser {
private:
    Tokenizer tokenizer;
    Expression parse(const std::vector<std::string> &tokens) const;
public:
    explicit Parser(const Tokenizer &t) : tokenizer(t) {}

    inline Expression parse(const std::string &string) const {
        return parse(tokenizer.tokenize(string));
    }

};

#endif
