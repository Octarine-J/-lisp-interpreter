#ifndef LISP_INTERPRETER_EVAL_ERROR_H
#define LISP_INTERPRETER_EVAL_ERROR_H

#include <sstream>

enum class EvalErrorType {
    EmptyExpression,
    UnknownSymbol,
    UnknownApplicative,
    NumberIsNotApplicative,
    ExpectedNumericArg,
    ExpectedSymbolicArg,
    RequiredAtLeastOneArg,
    RequiredNArgsExactly,
    ExpectedSingleToken
};

class EvalError : public std::runtime_error {
private:
    EvalErrorType error_type;
public:
    explicit EvalError(EvalErrorType err_type, std::initializer_list<std::string> params = {}) :
            runtime_error(get_description(err_type, params)), error_type(err_type) {
    }

    EvalErrorType get_type() const {
        return error_type;
    }

    const char* get_description(EvalErrorType errorType, std::initializer_list<std::string> params) const {
        std::stringstream ss;

        auto arg0 = (params.size() > 0) ? *params.begin() : "";
        auto arg1 = (params.size() > 1) ? *(params.begin() + 1) : "";

        switch (errorType) {
            case EvalErrorType::EmptyExpression:
                ss << "Empty expression";
                break;
            case EvalErrorType::UnknownSymbol:
                ss << "Unknown symbol: '" << arg0 << "'";
                break;
            case EvalErrorType::UnknownApplicative:
                ss << "Unknown applicative: '" << arg0 << "'";
                break;
            case EvalErrorType::NumberIsNotApplicative:
                ss << "A number '" << arg0 << "' cannot be used as a function";
                break;
            case EvalErrorType ::ExpectedNumericArg:
                ss << "Function '" << arg0 << "' expected a numeric argument, found '" << arg1 << "'";
                break;
            case EvalErrorType ::ExpectedSymbolicArg:
                ss << "Function '" << arg0 << "' expected a symbolic argument, found number '" << arg1 << "'";
                break;
            case EvalErrorType ::RequiredAtLeastOneArg:
                ss << "Function '" << arg0 << "' requires at least one argument";
                break;
            case EvalErrorType ::RequiredNArgsExactly:
                ss << "Function '" << arg0 << "' requires exactly " << arg1 << " args";
                break;
            case EvalErrorType ::ExpectedSingleToken:
                ss << "Expected a single token, found expression '" << arg0 << "'";
                break;
            default:
                break;
        }

        return ss.str().c_str();
    }
};

#endif
