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
    std::map<std::string, std::function<std::shared_ptr<EvaluatedExpression>(std::vector<std::shared_ptr<EvaluatedExpression>> args)>> env;

    std::vector<double> convertToNumericArgs(std::vector<std::shared_ptr<EvaluatedExpression>> args) const;

    void registerFunction(std::string name, std::function<std::shared_ptr<EvaluatedExpression>(std::vector<std::shared_ptr<EvaluatedExpression>> args)> function);

    void loadStdLib();

public:
    Interpreter(Parser p) : parser(p) {
        loadStdLib();
    }

    decltype(env) getEnv() const {
        return env;
    }

    std::shared_ptr<EvaluatedExpression> eval(const std::string& string) {
        return parser.parse(string)->eval();
    }
};

#endif
