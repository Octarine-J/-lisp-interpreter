#include "interpreter/interpreter.h"
#include "interpreter/eval_error.h"

void Interpreter::load_core_lib() {
    register_function("+", [this](std::vector<Expression> args) {
        if (args.empty()) {
            throw eval_error(EvalErrorType::RequiredAtLeastOneArg, {"+"});
        }

        auto numeric_args = this->to_numeric_args(args);
        double result = numeric_args[0];

        for (auto arg = numeric_args.begin() + 1; arg < numeric_args.end(); ++arg) {
            result += *arg;
        }

        return Expression(std::to_string(result));
    });

    register_function("*", [this](std::vector<Expression> args) {
        if (args.empty()) {
            throw eval_error(EvalErrorType::RequiredAtLeastOneArg, {"*"});
        }

        auto numeric_args = this->to_numeric_args(args);
        double result = numeric_args[0];

        for (auto arg = numeric_args.begin() + 1; arg < numeric_args.end(); ++arg) {
            result *= *arg;
        }

        return Expression(std::to_string(result));
    });

    register_function("-", [this](std::vector<Expression> args) {
        if (args.empty()) {
            throw eval_error(EvalErrorType::RequiredAtLeastOneArg, {"-"});
        }

        auto numeric_args = this->to_numeric_args(args);
        double result = numeric_args[0];

        for (auto arg = numeric_args.begin() + 1; arg < numeric_args.end(); ++arg) {
            result -= *arg;
        }

        return Expression(std::to_string(result));
    });

    register_function("/", [this](std::vector<Expression> args) {
        if (args.empty()) {
            throw eval_error(EvalErrorType::RequiredAtLeastOneArg, {"/"});
        }

        auto numeric_args = this->to_numeric_args(args);
        double result = numeric_args[0];
        double arg_product = 1;

        for (auto arg = numeric_args.begin() + 1; arg < numeric_args.end(); ++arg) {
            arg_product *= *arg;
        }

        result = result / arg_product;

        return Expression(std::to_string(result));
    });
}


void Interpreter::register_function(const std::string &name, std::function<Expression(std::vector<Expression> args)> function) {
    env.insert(std::make_pair(name, function));
}


std::vector<double> Interpreter::to_numeric_args(const std::vector<Expression> &args) const {
    std::vector<double> result;
    result.reserve(args.size());

    for (const auto &arg : args) {
        double value;
        try {
            value = std::stod(arg.get_value());
        } catch (const std::invalid_argument &e) {
            throw eval_error(EvalErrorType::ExpectedNumericArg, {arg.get_value()});
        }
        result.push_back(value);
    }

    return result;
}

