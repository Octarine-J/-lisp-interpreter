#ifndef LISP_INTERPRETER_EVAL_ERROR_H
#define LISP_INTERPRETER_EVAL_ERROR_H

#include <sstream>

namespace eval_error {
    class EvalError : public std::runtime_error {
    public:
        explicit EvalError(const char* error_message) : runtime_error(error_message) {}
    };

    class EmptyExpression : public EvalError {
    public:
        EmptyExpression() :
            EvalError("Empty expression") {}
    };

    class UnknownSymbol : public EvalError {
    public:
        explicit UnknownSymbol(const std::string &symbol) :
            EvalError(get_description(symbol)) {}

        static const char* get_description(const std::string &symbol) {
            std::stringstream ss;
            ss << "Unknown symbol: '" << symbol << "'";
            return ss.str().c_str();
        }
    };

    class UnknownApplicative : public EvalError {
    public:
        explicit UnknownApplicative(const std::string &symbol) :
            EvalError(get_description(symbol)) {}

        static const char* get_description(const std::string &symbol) {
            std::stringstream ss;
            ss << "Unknown applicative: '" << symbol << "'";
            return ss.str().c_str();
        }
    };

    class NumberIsNotApplicative : public EvalError {
    public:
        explicit NumberIsNotApplicative(double number) :
            EvalError(get_description(number)) {}

        static const char* get_description(double number) {
            std::stringstream ss;
            ss << "A number '" << number << "' cannot be used as a function";
            return ss.str().c_str();
        }
    };

    class ExpectedNumericArg : public EvalError {
    public:
        explicit ExpectedNumericArg(const std::string &function_name, const std::string &symbol) :
            EvalError(get_description(function_name, symbol)) {}

        static const char* get_description(const std::string &function_name, const std::string &symbol) {
            std::stringstream ss;
            ss << "Function '" << function_name << "' expected a numeric argument, found '" << symbol << "'";
            return ss.str().c_str();
        }
    };

    class ExpectedSymbolicArg : public EvalError {
    public:
        ExpectedSymbolicArg(const std::string &function_name, double actual_arg) :
            EvalError(get_description(function_name, actual_arg)) {}

        static const char* get_description(const std::string &function_name, double actual_arg) {
            std::stringstream ss;
            ss << "Function '" << function_name << "' expected a symbolic argument, found number '" << actual_arg << "'";
            return ss.str().c_str();
        }
    };

    class RequiredAtLeastOneArg : public EvalError {
    public:
        explicit RequiredAtLeastOneArg(const std::string &function_name) :
            EvalError(get_description(function_name)) {}

        static const char* get_description(const std::string &function_name) {
            std::stringstream ss;
            ss << "Function '" << function_name << "' requires at least one argument";
            return ss.str().c_str();
        }
    };

    class RequiredNumArgsExactly : public EvalError {
    public:
        RequiredNumArgsExactly(const std::string &function_name, int num_args) :
            EvalError(get_description(function_name, num_args)) {}

        static const char* get_description(const std::string &function_name, int num_args) {
            std::stringstream ss;
            ss << "Function '" << function_name << "' requires exactly " << num_args << " arguments";
            return ss.str().c_str();
        }
    };

    class ExpectedSingleToken : public EvalError {
    public:
        explicit ExpectedSingleToken(const Expression &expression) :
            EvalError(get_description(expression)) {}

        static const char* get_description(const Expression &expression) {
            std::stringstream ss;
            ss << "Expected a single token, found expression '" << to_string(expression) << "'";
            return ss.str().c_str();
        }
    };

}

#endif
