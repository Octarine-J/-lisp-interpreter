#include "interpreter.h"

void Interpreter::loadStdLib() {
    registerFunction("+", [this](std::vector<std::shared_ptr<Expression>> args) {
        double result = 0;
        for (auto arg : this->convertToNumericArgs(args)) {
            result += arg;
        }
        return std::make_shared<Expression>(std::to_string(result));
    });

    registerFunction("*", [this](std::vector<std::shared_ptr<Expression>> args) {
        double result = 1;
        for (auto arg : this->convertToNumericArgs(args)) {
            result *= arg;
        }
        return std::make_shared<Expression>(std::to_string(result));
    });
}


void Interpreter::registerFunction(const std::string &name, std::function<std::shared_ptr<Expression>(std::vector<std::shared_ptr<Expression>> args)> function) {
    env.insert(std::make_pair(name, function));
}


std::vector<double> Interpreter::convertToNumericArgs(const std::vector<std::shared_ptr<Expression>> &args) const {
    std::vector<double> result;
    for (const auto &arg : args) {
        result.push_back(std::stod(arg->get_value()));
    }
    return result;
}

