#include <memory>
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
Expression Parser::parse(const std::vector<std::string> &tokens) const {
    if (tokens.empty()) {
        throw parser_error(ParseErrorType::EmptyExpression);
    }

    std::stack<Expression> expression_stack;
    std::optional<Expression> result_expression;

    for (const auto &token : tokens) {
        if (token == "(") {
            if (result_expression.has_value()) {
                throw parser_error(ParseErrorType::TokenOutsideExpression);
            }
            expression_stack.push(Expression {});
        } else if (token == ")") {
            if (expression_stack.empty()) {
                throw parser_error(ParseErrorType::UnmatchedClosedParenthesis);
            }

            auto child_expression = expression_stack.top();
            if (child_expression.is_leaf()) {
                throw parser_error(ParseErrorType::EmptyExpression);
            }

            expression_stack.pop();

            if (expression_stack.empty()) {
                if (result_expression.has_value()) {
                    throw parser_error(ParseErrorType::TokenOutsideExpression);
                } else {
                    result_expression.emplace(child_expression);
                }
            } else {
                expression_stack.top().add_child(child_expression);
            }


        } else {
            if (expression_stack.empty()) {
                if (result_expression.has_value()) {
                    throw parser_error(ParseErrorType::TokenOutsideExpression);
                } else {
                    result_expression.emplace(Expression {token});
                }
            } else {
                expression_stack.top().add_child(Expression {token});
            }
        }
    }

    if (expression_stack.empty()) {
        if (result_expression.has_value()) {
            return result_expression.value();
        } else {
            throw parser_error(ParseErrorType::TokenOutsideExpression);
        }
    } else {
        throw parser_error(ParseErrorType::PrematureEndOfExpression);
    }
}
