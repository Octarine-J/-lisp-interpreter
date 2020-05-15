#ifndef LISP_INTERPRETER_ARGS_H
#define LISP_INTERPRETER_ARGS_H

#include "aliases.h"
#include "eval_error.h"

// Asserts that there is at least one argument
template <typename T>
void require_at_least_one_arg(const std::string &function_name, const std::vector<T> &args) {
    if (args.empty()) {
        throw eval_error::RequiredAtLeastOneArg(function_name);
    }
}

template <typename T>
std::pair<T, std::vector<T>> to_head_tail(const std::string &function_name, const std::vector<T> &args) {
    require_at_least_one_arg(function_name, args);
    return std::make_pair(args[0], std::vector(args.cbegin() + 1, args.cend()));
}

// Converts arguments to numeric values
std::vector<double> to_numeric_args(const std::string &function_name, const LispFunctionArgs &args);

std::pair<double, std::vector<double>> to_numeric_args_head_tail(const std::string &function_name, const LispFunctionArgs &args);

void require_symbolic_arg(const EvaluatedExpression &expression);

#endif
