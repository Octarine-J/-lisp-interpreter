#include <stack>
#include "parser.h"

/**
 * Converts a vector of tokens into a Lisp expression,
 * which may contain nested subexpressions.
 * For example, "(* (+ 30 5) 12)"  ->  "Expr< * Expr< + 30 5 > 12 >"
 *
 * @param tokens - Lisp program tokens
 * @return the top-level expression
 */
std::shared_ptr<Expression> Parser::parse(const std::vector<std::string> &tokens) const {
    if (tokens.empty()) {
        throw parser_error(0, "empty expression");
    }

    std::stack<std::shared_ptr<Expression>> expression_stack;
    std::shared_ptr<Expression> current_expression;

    auto num_tokens = tokens.size();

    for (size_t i = 0; i < num_tokens - 1; ++i) {
        if (tokens[i] == "(") {
            auto expression = std::make_shared<Expression>();
            expression_stack.push(expression);
            current_expression = expression;
        } else if (tokens[i] == ")") {
            if (expression_stack.empty()) {
                throw parser_error(i, "closed parenthesis outside of an expression");
            }

            if (current_expression->is_leaf()) {
                throw parser_error(i, "empty expression");
            }

            expression_stack.pop();

            if (expression_stack.empty()) {
                throw parser_error(i, "closed parenthesis outside of an expression");
            }

            auto previous_expression = expression_stack.top();
            previous_expression->add_child(current_expression);
            current_expression = previous_expression;
        } else {
            auto token = std::make_shared<Expression>(tokens[i]);
            current_expression->add_child(token);
        }
    }

    if (current_expression == nullptr || current_expression->is_leaf()) {
        throw parser_error(num_tokens - 1, "empty expression");
    }

    if (tokens[num_tokens - 1] != ")" || expression_stack.size() != 1) {
        throw parser_error(num_tokens - 1, "premature end of an expression");
    }

    return current_expression;
}

/**
 * Splits a string into tokens.
 * For example, "(+ 3 4)" -> ["(", "+", "3", "4", ")"]
 *
 * @param string - Input string
 * @return a vector of tokens
 */
std::vector<std::string> Parser::tokenize(const std::string &string) const {
    std::vector<std::string> tokens;
    std::string acc;
    for (char c : string) {
        switch (c) {
            case '(':
            case ')':
                if (!acc.empty()) {
                    tokens.push_back(acc);
                    acc.clear();
                }
                tokens.emplace_back(1, c);
                break;
            case ' ':
                if (!acc.empty()) {
                    tokens.push_back(acc);
                    acc.clear();
                }
                break;
            default:
                acc += c;
        }
    }

    if (!acc.empty()) {
        throw parser_error(string.size() - 1, "premature end of an expression");
    }

    return tokens;
}
