#ifndef LISP_INTERPRETER_PARSE_H
#define LISP_INTERPRETER_PARSE_H

#include <string>
#include <vector>
#include "expressions.h"

class Parser {
private:
    std::vector<std::string> tokenize(std::string string);

    std::shared_ptr<Expression> parse(std::vector<std::string> tokens);
public:
    std::shared_ptr<Expression> parse(std::string string);
};


#endif
