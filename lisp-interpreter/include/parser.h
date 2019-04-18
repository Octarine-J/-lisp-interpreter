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
    inline std::shared_ptr<Expression> parse(const std::string &string) const {
        return parse(tokenize(string));
    }
};

class parser_error : public std::runtime_error {
public:
    parser_error(int pos, const std::string &message) :
        runtime_error(get_description(pos, message)) {
    }

    const char* get_description(int pos, const std::string &message) const {
        std::string result = "Parser error at pos ";
        result += std::to_string(pos) + ": ";
        result += message;
        return result.c_str();
    }
};


#endif
