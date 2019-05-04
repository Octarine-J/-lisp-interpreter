#include "interpreter/interpreter.h"
#include "interpreter/eval_error.h"

void Interpreter::load_core_lib() {
    register_function("+", [this](LispFunctionArgs args) {
        if (args.empty()) {
            throw eval_error::RequiredAtLeastOneArg("+");
        }

        auto numeric_args = this->to_numeric_args("+", args);
        double result = numeric_args[0];

        for (auto arg = numeric_args.begin() + 1; arg < numeric_args.end(); ++arg) {
            result += *arg;
        }

        return EvaluatedExpression {result};
    });

    register_function("*", [this](LispFunctionArgs args) {
        if (args.empty()) {
            throw eval_error::RequiredAtLeastOneArg("*");
        }

        auto numeric_args = this->to_numeric_args("*", args);
        double result = numeric_args[0];

        for (auto arg = numeric_args.begin() + 1; arg < numeric_args.end(); ++arg) {
            result *= *arg;
        }

        return EvaluatedExpression {result};
    });

    register_function("-", [this](LispFunctionArgs args) {
        if (args.empty()) {
            throw eval_error::RequiredAtLeastOneArg("-");
        }

        auto numeric_args = this->to_numeric_args("-", args);
        double result = numeric_args[0];

        for (auto arg = numeric_args.begin() + 1; arg < numeric_args.end(); ++arg) {
            result -= *arg;
        }

        return EvaluatedExpression {result};
    });

    register_function("/", [this](LispFunctionArgs args) {
        if (args.empty()) {
            throw eval_error::RequiredAtLeastOneArg("/");
        }

        auto numeric_args = this->to_numeric_args("/", args);
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


std::vector<double> Interpreter::to_numeric_args(const std::string &function_name, const LispFunctionArgs &args) const {
    std::vector<double> result;
    result.reserve(args.size());

    for (const auto &arg : args) {
        if (arg.is_symbol()) {
            throw eval_error::ExpectedNumericArg(function_name, arg.get_symbol());
        }
        result.push_back(arg.get_number());
    }

    return result;
}

std::optional<EvaluatedExpression> Interpreter::find_variable(const std::string &name) {
    return find_in_context(variables, name);
}

std::optional<LispFunction> Interpreter::find_function(const std::string &name) {
    return find_in_context(env, name);
}

void Interpreter::set_variable(VariableContext &context, const std::string &name, const EvaluatedExpression &expression) {
    context.insert(std::make_pair(name, expression));
}

EvaluatedExpression Interpreter::apply(const EvaluatedExpression &applicative, const std::vector<EvaluatedExpression> &args) {
    if (applicative.is_number()) {
        throw eval_error::NumberIsNotApplicative(applicative.get_number());
    }

    auto function_name = applicative.get_symbol();
    auto function = find_function(function_name);

    if (function.has_value()) {
        auto f = function.value();
        return f(args);
    } else {
        throw eval_error::UnknownApplicative(function_name);
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
        throw eval_error::RequiredNumArgsExactly("define", 2);
    }

    auto definition = input_args[1];
    if (definition.is_leaf()) {
        return define_variable(variables, definition, input_args[2]);
    } else {
        std::vector<Expression> args(input_args.cbegin() + 2, input_args.cend());
        return define_function(definition, args);
    }
}

EvaluatedExpression Interpreter::define_variable(VariableContext &context, const Expression &lhs, const Expression &rhs) {
    auto variable_name = eval(lhs.get_value());
    if (variable_name.is_number()) {
        throw eval_error::ExpectedSymbolicArg("define", variable_name.get_number());
    }

    set_variable(context, variable_name.get_symbol(), eval(rhs));

    return EvaluatedExpression {variable_name};
}

EvaluatedExpression Interpreter::define_function(const Expression &lhs, const std::vector<Expression> &args) {
    auto lhs_children = lhs.get_children();
    if (lhs_children.size() <= 1) {
        throw eval_error::RequiredAtLeastOneArg("define (function)");
    }

    for (const auto &child : lhs_children) {
        if (!child.is_leaf()) {
            throw eval_error::ExpectedSingleToken(child);
        }
    }

    auto function_name = lhs_children[0].get_value();

    register_function(function_name, [this](LispFunctionArgs args) {


        return EvaluatedExpression {1};

        //return eval(args[2]);
    });

    return EvaluatedExpression {function_name};
}

