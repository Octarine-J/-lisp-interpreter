#include "interpreter/interpreter.h"
#include "interpreter/eval_error.h"

void Interpreter::load_core_lib() {
    register_function("+", [this](LispFunctionArgs args) {
        if (args.empty()) {
            throw EvalError(EvalErrorType::RequiredAtLeastOneArg, {"+"});
        }

        auto numeric_args = this->to_numeric_args(args);
        double result = numeric_args[0];

        for (auto arg = numeric_args.begin() + 1; arg < numeric_args.end(); ++arg) {
            result += *arg;
        }

        return EvaluatedExpression {result};
    });

    register_function("*", [this](LispFunctionArgs args) {
        if (args.empty()) {
            throw EvalError(EvalErrorType::RequiredAtLeastOneArg, {"*"});
        }

        auto numeric_args = this->to_numeric_args(args);
        double result = numeric_args[0];

        for (auto arg = numeric_args.begin() + 1; arg < numeric_args.end(); ++arg) {
            result *= *arg;
        }

        return EvaluatedExpression {result};
    });

    register_function("-", [this](LispFunctionArgs args) {
        if (args.empty()) {
            throw EvalError(EvalErrorType::RequiredAtLeastOneArg, {"-"});
        }

        auto numeric_args = this->to_numeric_args(args);
        double result = numeric_args[0];

        for (auto arg = numeric_args.begin() + 1; arg < numeric_args.end(); ++arg) {
            result -= *arg;
        }

        return EvaluatedExpression {result};
    });

    register_function("/", [this](LispFunctionArgs args) {
        if (args.empty()) {
            throw EvalError(EvalErrorType::RequiredAtLeastOneArg, {"/"});
        }

        auto numeric_args = this->to_numeric_args(args);
        double result = numeric_args[0];
        double arg_product = 1;

        for (auto arg = numeric_args.begin() + 1; arg < numeric_args.end(); ++arg) {
            arg_product *= *arg;
        }

        result = result / arg_product;

        return EvaluatedExpression {result};
    });
}


void Interpreter::register_function(const std::string &name, LispFunction function) {
    env.insert(std::make_pair(name, function));
}


std::vector<double> Interpreter::to_numeric_args(const std::vector<EvaluatedExpression> &args) const {
    std::vector<double> result;
    result.reserve(args.size());

    for (const auto &arg : args) {
        if (arg.is_symbol()) {
            throw EvalError(EvalErrorType::ExpectedNumericArg, {arg.get_symbol()});
        }
        result.push_back(arg.get_number());
    }

    return result;
}

std::optional<EvaluatedExpression> Interpreter::find_variable(const std::string &name) {
    auto pos = variables.find(name);
    if (pos == variables.end()) {
        return std::nullopt;
    } else {
        return pos->second;
    }
}

std::optional<LispFunction> Interpreter::find_function(const std::string &name) {
    auto pos = env.find(name);
    if (pos == env.end()) {
        return std::nullopt;
    } else {
        return pos->second;
    }
}

void Interpreter::define_variable(const std::string &name, const EvaluatedExpression &expression) {
    variables.insert(std::make_pair(name, expression));
}

EvaluatedExpression Interpreter::apply(const EvaluatedExpression &applicative, const std::vector<EvaluatedExpression> &args) {
    if (applicative.is_number()) {
        throw EvalError(EvalErrorType::NumberIsNotApplicative, {std::to_string(applicative.get_number())});
    }

    auto function_name = applicative.get_symbol();
    auto function = find_function(function_name);

    if (function.has_value()) {
        auto f = function.value();
        return f(args);
    } else {
        throw EvalError(EvalErrorType::UnknownApplicative, {function_name});
    }
}

EvaluatedExpression Interpreter::eval(const Expression &expression) {
    if (expression.is_leaf()) {
        auto variable = find_variable(expression.get_value());
        if (variable.has_value()) {
            return variable.value();
        }

        return eval_leaf(expression.get_value());
    }

    auto children = expression.get_children();
    auto applicative = eval(children[0]);

    if (is_define(applicative)) {
        return define(children);
    } else {
        std::vector<EvaluatedExpression> args;
        for (int i = 1; i < children.size(); ++i) {
            args.push_back(eval(children[i]));
        }

        return apply(applicative, args);
    }
}

EvaluatedExpression Interpreter::eval_leaf(const std::string &value) {
    try {
        return EvaluatedExpression { std::stod(value) };
    } catch (const std::invalid_argument &e) {
        return EvaluatedExpression {value};
    }
}

EvaluatedExpression Interpreter::define(const std::vector<Expression> &input_args) {
    if (input_args.size() != 3) {
        // expected (define name expr)
        throw EvalError(EvalErrorType::RequiredNArgsExactly, {"define", "2"});
    }

    auto definition = input_args[1];
    if (!definition.is_leaf()) {
        throw EvalError(EvalErrorType::ExpectedSingleToken);
    }

    auto variable_name = eval(definition.get_value());
    if (variable_name.is_number()) {
        throw EvalError(EvalErrorType::ExpectedSymbolicArg, {"define", std::to_string(variable_name.get_number())});
    }

    define_variable(variable_name.get_symbol(), eval(input_args[2]));

//        register_function(definition.get_value(), [this](std::vector<Expression> args) {
//            return eval(args[2]);
//        });

    return EvaluatedExpression {variable_name};
}
