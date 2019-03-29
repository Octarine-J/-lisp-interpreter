#include "interpreter.h"

void Interpreter::loadStdLib() {
    registerFunction("+", [this](std::vector<std::shared_ptr<EvaluatedExpression>> args) {
        double result = 0;
        for (auto arg : this->convertToNumericArgs(args)) {
            result += arg;
        }
        return std::make_shared<Number>(result);
    });

    registerFunction("*", [this](std::vector<std::shared_ptr<EvaluatedExpression>> args) {
        double result = 1;
        for (auto arg : this->convertToNumericArgs(args)) {
            result *= arg;
        }
        return std::make_shared<Number>(result);
    });
}


void Interpreter::registerFunction(std::string name, std::function<std::shared_ptr<EvaluatedExpression>(std::vector<std::shared_ptr<EvaluatedExpression>> args)> function) {
    env.insert(std::make_pair(name, function));
}


std::vector<double> Interpreter::convertToNumericArgs(std::vector<std::shared_ptr<EvaluatedExpression>> args) const {
    std::vector<double> result;
    for (auto arg : args) {
        result.push_back(std::stod(arg->toString()));
    }
    return result;
}

