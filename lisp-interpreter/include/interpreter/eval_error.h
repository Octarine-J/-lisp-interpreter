#ifndef LISP_INTERPRETER_EVAL_ERROR_H
#define LISP_INTERPRETER_EVAL_ERROR_H

enum class EvalErrorType {
    EmptyExpression,
    UnknownSymbol,
    NumberIsNotApplicative,
    ExpectedNumericArg,
    RequiredAtLeastOneArg,
    RequiredNArgsExactly,
    ExpectedSingleToken
};

class eval_error : public std::runtime_error {
private:
    EvalErrorType error_type;
public:
    explicit eval_error(EvalErrorType err_type, std::initializer_list<std::string> params = {}) :
            runtime_error(get_description(err_type, params)), error_type(err_type) {
    }

    const char* get_description(EvalErrorType errorType, std::initializer_list<std::string> params) const {
        std::string msg;
        switch (errorType) {
            case EvalErrorType::EmptyExpression:
                msg = "Empty expression";
                break;
            case EvalErrorType::UnknownSymbol:
                return "Unknown symbol";
            case EvalErrorType::NumberIsNotApplicative:
                return "A number cannot be used as a function";
            case EvalErrorType ::ExpectedNumericArg:
                return "Function expected a numeric argument";
            case EvalErrorType ::RequiredAtLeastOneArg:
                return "Function requires at least one argument";
            case EvalErrorType ::RequiredNArgsExactly:
                return "Function requires exact number of args";
            case EvalErrorType ::ExpectedSingleToken:
                return "Expected a single token, found expression";
            default:
                return "";
        }

        if (params.size()) {
            msg += ": ";
            for (const auto &param : params) {
                msg += param + " ";
            }
        }

        return msg.c_str();
    }
};

#endif
