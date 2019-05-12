#include "interpreter/interpreter.h"
#include "interpreter/args.h"

void Interpreter::load_core_lib() {
    env.register_function("+", [](auto args) {
        auto numeric_args = to_numeric_args_head_tail("+", args);

        double result = numeric_args.first;
        for (auto arg : numeric_args.second) {
            result += arg;
        }

        return EvaluatedExpression {result};
    });

    env.register_function("*", [](auto args) {
        auto numeric_args = to_numeric_args_head_tail("*", args);

        double result = numeric_args.first;
        for (auto arg : numeric_args.second) {
            result *= arg;
        }

        return EvaluatedExpression {result};
    });

    env.register_function("-", [](auto args) {
        auto numeric_args = to_numeric_args_head_tail("-", args);

        double result = numeric_args.first;
        for (auto arg : numeric_args.second) {
            result -= arg;
        }

        return EvaluatedExpression {result};
    });

    env.register_function("/", [](auto args) {
        auto numeric_args = to_numeric_args_head_tail("/", args);

        double arg_product = 1;
        for (auto arg : numeric_args.second) {
            arg_product *= arg;
        }

        return EvaluatedExpression {numeric_args.first / arg_product};
    });
}