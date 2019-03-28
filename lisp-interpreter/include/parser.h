#ifndef LISP_INTERPRETER_PARSE_H
#define LISP_INTERPRETER_PARSE_H

#include <string>
#include <vector>
#include "expressions.h"

class Parser {
private:
    std::vector<std::string> tokenize(const std::string &string) const;

    std::shared_ptr<Expression> parse(const std::vector<std::string> &tokens) const;
public:
    std::shared_ptr<Expression> parse(const std::string &string) const;
};


#endif
