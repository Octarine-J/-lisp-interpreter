#include <utility>

#ifndef LISP_INTERPRETATOR_EVAL_EXPRESSIONS_H
#define LISP_INTERPRETATOR_EVAL_EXPRESSIONS_H

#include <memory>
#include <string>
#include <vector>

class EvaluatedExpression {
public:
    virtual std::shared_ptr<EvaluatedExpression> apply(std::vector<std::shared_ptr<EvaluatedExpression>> args) const = 0;
    virtual std::string toString() const = 0;
};

class Number : public EvaluatedExpression {
private:
    double value;
public:
    Number(double val) : value(val) {}

    double getValue() const {
        return value;
    }

    virtual std::shared_ptr<EvaluatedExpression> apply(std::vector<std::shared_ptr<EvaluatedExpression>> args) const override {
        throw std::runtime_error("number is not an applicative");
    }

    virtual std::string toString() const override {
        return std::to_string(value);
    }
};

class Symbol : public EvaluatedExpression {
private:
    std::string value;

    std::vector<double> convertToNumericArgs(std::vector<std::shared_ptr<EvaluatedExpression>> args) const {
        std::vector<double> result;
        for (auto arg : args) {
            result.push_back(std::stod(arg->toString()));
        }
        return result;
    }

public:
    Symbol(std::string val) : value(std::move(val)) {}

    virtual std::shared_ptr<EvaluatedExpression> apply(std::vector<std::shared_ptr<EvaluatedExpression>> args) const override {
        if (value == "+") {
            double sum = 0;
            for (auto arg : convertToNumericArgs(args)) {
                sum += arg;
            }
            return std::make_shared<Number>(sum);
        } else if (value == "*") {
            double product = 1;
            for (auto arg : convertToNumericArgs(args)) {
                product *= arg;
            }
            return std::make_shared<Number>(product);
        } else {
            throw std::runtime_error("unknown applicative: " + value);
        }
    };

    virtual std::string toString() const override {
        return value;
    };
};


#endif //LISP_INTERPRETATOR_EVAL_EXPRESSIONS_H
