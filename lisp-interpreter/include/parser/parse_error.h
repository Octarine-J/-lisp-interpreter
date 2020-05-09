#ifndef LISP_INTERPRETER_PARSE_ERROR_H
#define LISP_INTERPRETER_PARSE_ERROR_H

#include <stdexcept>
#include <string>

enum class ParseErrorType {
    EmptyExpression,
    PrematureEndOfExpression,
    TokenOutsideExpression,
    UnmatchedClosedParenthesis
};

class parser_error : public std::runtime_error {
private:
    ParseErrorType error_type;
public:
    explicit parser_error(ParseErrorType err_type) :
        runtime_error(get_description(err_type)), error_type(err_type) {
    }

    const char* get_description(ParseErrorType errorType) const {
        switch (errorType) {
            case ParseErrorType::EmptyExpression:
                return "Empty expression";
            case ParseErrorType::PrematureEndOfExpression:
                return "Input ended before expression is closed";
            case ParseErrorType::TokenOutsideExpression:
                return "Found a token outside of any expression";
            case ParseErrorType ::UnmatchedClosedParenthesis:
                return "Found an unmatched closed parenthesis";
            default:
                return "";
        }
    }
};

#endif
