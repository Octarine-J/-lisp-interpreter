#ifndef LISP_INTERPRETER_EXPRESSIONS_H
#define LISP_INTERPRETER_EXPRESSIONS_H

#include <memory>
#include <vector>
#include "eval_expressions.h"

class Expression {
private:
    std::vector<std::shared_ptr<Expression>> subexpressions;
public:
    void add(const std::shared_ptr<Expression> &expression) {
        subexpressions.push_back(expression);
    }

    bool empty() const {
        return subexpressions.empty();
    }

    virtual std::shared_ptr<EvaluatedExpression> eval() const {
        if (subexpressions.empty()) {
            throw std::runtime_error("empty expression");
        }

        auto applicative = subexpressions[0]->eval();

        std::vector<std::shared_ptr<EvaluatedExpression>> args;
        for (int i = 1; i < subexpressions.size(); ++i) {
            args.push_back(subexpressions[i]->eval());
        }

        return applicative->apply(args);
    }

    virtual std::string toString() const {
        std::string result = "Expr< ";
        for (const auto &expression : subexpressions) {
            result += expression->toString() + " ";
        }
        result += ">";
        return result;
    }
};

class Token : public Expression {
private:
    std::string value;
public:
    Token(std::string val) : value(std::move(val)) {}

    virtual std::shared_ptr<EvaluatedExpression> eval() const override {
        try {
            return std::make_shared<Number>(std::stod(value));
        } catch (std::invalid_argument e) {
            return std::make_shared<Symbol>(value);
        }
    }

    virtual std::string toString() const override {
        return value;
    }
};


#endif
