#include "interpreter/args.h"

std::vector<double> to_numeric_args(const std::string &function_name, const LispFunctionArgs &args) {
    std::vector<double> result;
    result.reserve(args.size());

    for (const auto &arg : args) {
        if (not arg.is_number()) {
            throw eval_error::ExpectedNumericArg(function_name, arg.to_string());
        }
        result.push_back(arg.get_number());
    }

    return result;
}

std::pair<double, std::vector<double>> to_numeric_args_head_tail(const std::string &function_name, const LispFunctionArgs &args) {
    return to_head_tail(function_name, to_numeric_args(function_name, args));
}

void require_symbolic_arg(const EvaluatedExpression &expression) {
    if (not expression.is_symbol()) {
        throw eval_error::UnacceptableApplicative(expression);
    }
}
