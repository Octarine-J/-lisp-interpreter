#ifndef LISP_INTERPRETER_EVAL_EXPRESSIONS_H
#define LISP_INTERPRETER_EVAL_EXPRESSIONS_H

#include <memory>
#include <string>
#include <vector>
#include "interpreter.h"

class EvaluatedExpression {
private:
    std::shared_ptr<Interpreter> interpreter;

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
      auto env = interpreter->getEnv();
      auto pos = env.find(value);
      if (pos == env.end()) {
	  throw std::runtime_error("unknown applicative: " + value);
      }
      return pos->second();
    };

    virtual std::string toString() const override {
        return value;
    };
};


#endif
