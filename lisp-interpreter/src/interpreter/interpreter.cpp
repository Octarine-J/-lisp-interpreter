#include "interpreter/interpreter.h"
#include "interpreter/eval_error.h"
#include "interpreter/args.h"


std::optional<EvaluatedExpression> Interpreter::find_variable(const std::string &name, const Context &local_context) const {
    auto result = env.find_variable(name);
    return result.has_value() ? result : local_context.find_variable(name);
}

std::optional<LispFunction> Interpreter::find_function(const std::string &name) const {
    return env.find_function(name);
}

LispFunction Interpreter::find_function(const EvaluatedExpression &applicative) const {
    auto function_name = applicative.get_symbol();
    auto function = find_function(function_name);

    if (function.has_value()) {
        return function.value();
    } else {
        throw eval_error::UnknownApplicative(function_name);
    }
}

EvaluatedExpression Interpreter::apply(const EvaluatedExpression &applicative, const std::vector<EvaluatedExpression> &args) {
    require_symbolic_arg(applicative);

    auto f = find_function(applicative);
    return f(args);
}

// Applicative order
EvaluatedExpression Interpreter::eval(const Expression &expression, Context local_context) {
    if (expression.is_leaf()) {
        auto variable = find_variable(expression.get_value(), local_context);
        if (variable.has_value()) {
            return variable.value();
        }

        return eval_leaf(expression.get_value());
    }

    auto children = expression.get_children();
    auto applicative = eval(children[0], local_context);

    if (is_define(applicative)) {
        return define(children, local_context);
    } else {
        std::vector<EvaluatedExpression> args;
        for (auto i = 1u; i < children.size(); ++i) {
            args.push_back(eval(children[i], local_context));
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

EvaluatedExpression Interpreter::define(const std::vector<Expression> &input_args, const Context &local_context) {
    if (input_args.size() != 3) {
        // expected: (define lhs rhs), for example: (define x 3) or (define (add x y) (x + y))
        throw eval_error::RequiredNumArgsExactly("define", 2);
    }

    auto lhs = input_args[1];
    auto rhs = input_args[2];

    if (lhs.is_leaf()) {
        auto variable_value = eval(input_args[2], local_context);
        return define_variable(env, lhs, variable_value);
    } else {
        return define_function(lhs, rhs);
    }
}

EvaluatedExpression Interpreter::define_variable(Context &context, const Expression &lhs, const EvaluatedExpression &rhs) {
    auto variable_name = eval(lhs.get_value());
    if (variable_name.is_number()) {
        throw eval_error::ExpectedSymbolicArg("define", variable_name.get_number());
    }

    context.set_variable(variable_name.get_symbol(), rhs);

    return EvaluatedExpression {variable_name};
}

EvaluatedExpression Interpreter::define_function(const Expression &lhs, Expression rhs) {
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

    env.register_function(function_name, [this,
                                          function_name,
                                          function_args = std::vector<Expression>(lhs_children.cbegin() + 1, lhs_children.cend()),
                                          function_body = std::move(rhs)](LispFunctionArgs args) {
        auto num_function_args = function_args.size();
        if (args.size() != num_function_args) {
            throw eval_error::RequiredNumArgsExactly(function_name, num_function_args);
        }

        Context local_context;
        for (auto i = 0u; i < num_function_args; ++i) {
            local_context.set_variable(function_args[i].get_value(), args[i]);
        }

//        local_context.set_variable()

        //return EvaluatedExpression {1};

        return eval(function_body, local_context);
    });

    return EvaluatedExpression {function_name};
}

