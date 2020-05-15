#ifndef LISP_INTERPRETER_EVAL_ERROR_H
#define LISP_INTERPRETER_EVAL_ERROR_H

#include <stdexcept>

#include "parser/expression.h"
#include "interpreter/eval_expression.h"

using namespace std::string_literals;

namespace eval_error {
    class EvalError : public std::runtime_error {
    public:
        explicit EvalError(const std::string &error_message) : runtime_error(error_message.c_str()) {}
    };

    class UnknownApplicative : public EvalError {
    public:
        explicit UnknownApplicative(const std::string &symbol) :
            EvalError(get_description(symbol)) {}

        static std::string get_description(const std::string &symbol) {
            return "Unknown function: '"s + symbol + "'";
        }
    };

    class UnacceptableApplicative : public EvalError {
    public:
        explicit UnacceptableApplicative(const EvaluatedExpression &expression) :
            EvalError(get_description(expression)) {}

        static std::string get_description(const EvaluatedExpression &expression) {
            return "A non-symbol '"s + expression.to_string() + "' cannot be used as a function";
        }
    };

    class ExpectedNumericArg : public EvalError {
    public:
        explicit ExpectedNumericArg(const std::string &function_name, const std::string &symbol) :
            EvalError(get_description(function_name, symbol)) {}

        static std::string get_description(const std::string &function_name, const std::string &symbol) {
            return "Function '"s + function_name + "' expected a numeric argument, found '" + symbol + "'";
        }
    };

    class ExpectedSymbolicArg : public EvalError {
    public:
        ExpectedSymbolicArg(const std::string &function_name, double actual_arg) :
            EvalError(get_description(function_name, actual_arg)) {}

        static std::string get_description(const std::string &function_name, double actual_arg) {
            return "Function '"s + function_name + "' expected a symbolic argument, found number '"
                + std::to_string(actual_arg) + "'";
        }
    };

    class RequiredAtLeastOneArg : public EvalError {
    public:
        explicit RequiredAtLeastOneArg(const std::string &function_name) :
            EvalError(get_description(function_name)) {}

        static std::string get_description(const std::string &function_name) {
            return "Function '"s + function_name + "' requires at least one argument";
        }
    };

    class RequiredNumArgsExactly : public EvalError {
    public:
        RequiredNumArgsExactly(const std::string &function_name, int num_args) :
            EvalError(get_description(function_name, num_args)) {}

        static std::string get_description(const std::string &function_name, int num_args) {
            return "Function '"s + function_name + "' requires exactly " + std::to_string(num_args) + " arguments";
        }
    };

    class ExpectedSingleToken : public EvalError {
    public:
        explicit ExpectedSingleToken(const Expression &expression) :
            EvalError(get_description(expression)) {}

        static std::string get_description(const Expression &expression) {
            return "Expected a single token, found expression '"s + to_string(expression) + "'";
        }
    };

}

#endif
