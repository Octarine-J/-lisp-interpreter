#ifndef LISP_INTERPRETER_INTERPRETER_H
#define LISP_INTERPRETER_INTERPRETER_H

#include <functional>
#include <map>
#include <string>
#include <vector>
#include "parser.h"

class Interpreter {
private:
    Parser parser;
    std::map<std::string, std::function<Expression(std::vector<Expression> args)>> env;

    std::vector<double> convertToNumericArgs(const std::vector<Expression> &args) const;

    void registerFunction(const std::string &name, std::function<Expression(std::vector<Expression> args)> function);

    void loadStdLib();

public:
    explicit Interpreter(Parser p) : parser(p) {
        loadStdLib();
    }

    Expression eval(const std::string& string) {
        return eval(parser.parse(string));
    }

    Expression eval(const Expression &expression) {
        auto value = expression.get_value();
        auto children = expression.get_children();

        if (expression.is_leaf()) {
            return expression;
        }

        auto applicative = eval(children[0]);

        std::vector<Expression> args;
        for (int i = 1; i < children.size(); ++i) {
            args.push_back(eval(children[i]));
        }

        return apply(applicative, args);
    }


    Expression apply(const Expression &applicative, const std::vector<Expression> &args) {
        auto pos = env.find(applicative.get_value());
        if (pos == env.end()) {
            throw std::runtime_error("unknown applicative: " + applicative.get_value());
        }

        return pos->second(args);
    }

};

#endif
