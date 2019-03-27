#include <stack>
#include "parse.h"

Expression parse(std::vector<std::string> tokens) {
    if (tokens.empty()) {
        throw std::runtime_error("empty expression");
    }

    std::stack<std::shared_ptr<Expression>> expressionStack;
    std::shared_ptr<Expression> currentExpression;

    for (size_t i = 0, n = tokens.size(); i < n; ++i) {
        if (tokens[i] == "(") {
            auto expression = std::make_shared<Expression>();
            expressionStack.push(expression);
            currentExpression = expression;
        } else if (tokens[i] == ")") {
            expressionStack.pop();
            if (expressionStack.empty()) {
                if (i != n - 1) {
                    throw std::runtime_error("premature end of the expression");
                }
            } else {
                auto previousExpression = expressionStack.top();
                previousExpression->addExpression(currentExpression);
                currentExpression = previousExpression;
            }
        } else {
            auto token = std::make_shared<Token>(tokens[i]);
            currentExpression->addExpression(token);
        }
    }

    return *currentExpression;
}

std::vector<std::string> tokenize(std::string string) {
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
    return tokens;
}
