#ifndef LISP_INTERPRETER_EVAL_ERROR_H
#define LISP_INTERPRETER_EVAL_ERROR_H

#include "parser/expression.h"

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
            return std::string("Unknown function: '") + symbol + "'";
        }
    };

    class NumberIsNotApplicative : public EvalError {
    public:
        explicit NumberIsNotApplicative(double number) :
            EvalError(get_description(number)) {}

        static std::string get_description(double number) {
            return std::string("A number '") + std::to_string(number) + "' cannot be used as a function";
        }
    };

    class ExpectedNumericArg : public EvalError {
    public:
        explicit ExpectedNumericArg(const std::string &function_name, const std::string &symbol) :
            EvalError(get_description(function_name, symbol)) {}

        static std::string get_description(const std::string &function_name, const std::string &symbol) {
            return std::string("Function '") + function_name + "' expected a numeric argument, found '" + symbol + "'";
        }
    };

    class ExpectedSymbolicArg : public EvalError {
    public:
        ExpectedSymbolicArg(const std::string &function_name, double actual_arg) :
            EvalError(get_description(function_name, actual_arg)) {}

        static std::string get_description(const std::string &function_name, double actual_arg) {
            return std::string("Function '") + function_name + "' expected a symbolic argument, found number '"
                + std::to_string(actual_arg) + "'";
        }
    };

    class RequiredAtLeastOneArg : public EvalError {
    public:
        explicit RequiredAtLeastOneArg(const std::string &function_name) :
            EvalError(get_description(function_name)) {}

        static std::string get_description(const std::string &function_name) {
            return std::string("Function '") + function_name + "' requires at least one argument";
        }
    };

    class RequiredNumArgsExactly : public EvalError {
    public:
        RequiredNumArgsExactly(const std::string &function_name, int num_args) :
            EvalError(get_description(function_name, num_args)) {}

        static std::string get_description(const std::string &function_name, int num_args) {
            return std::string("Function '") + function_name + "' requires exactly " + std::to_string(num_args) + " arguments";
        }
    };

    class ExpectedSingleToken : public EvalError {
    public:
        explicit ExpectedSingleToken(const Expression &expression) :
            EvalError(get_description(expression)) {}

        static std::string get_description(const Expression &expression) {
            return std::string("Expected a single token, found expression '") + to_string(expression) + "'";
        }
    };

}

#endif
