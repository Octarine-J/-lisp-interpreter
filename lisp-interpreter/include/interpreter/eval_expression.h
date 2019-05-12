#ifndef LISP_INTERPRETER_EVAL_EXPRESSION_H
#define LISP_INTERPRETER_EVAL_EXPRESSION_H

#include <string>

enum class EvaluatedExpressionType {
    Number, Symbol
};

class EvaluatedExpression {
private:
    EvaluatedExpressionType type;
    double number;
    std::string symbol;
public:
    explicit EvaluatedExpression(double num) : number(num) {
        type = EvaluatedExpressionType::Number;
    }

    explicit EvaluatedExpression(std::string s) : symbol(std::move(s)) {
        type = EvaluatedExpressionType::Symbol;
        number = 0;
    }

    bool is_number() const {
        return type == EvaluatedExpressionType::Number;
    }

    double get_number() const {
        return number;
    }

    bool is_symbol() const {
        return type == EvaluatedExpressionType::Symbol;
    }

    std::string get_symbol() const {
        return symbol;
    }

    std::string to_string() const {
        switch (type) {
            case EvaluatedExpressionType::Number:
                return std::to_string(number);
            case EvaluatedExpressionType::Symbol:
                return symbol;
            default:
                return {};
        }
    }
};


#endif
