#ifndef LISP_INTERPRETER_INTERPRETER_H
#define LISP_INTERPRETER_INTERPRETER_H

#include <functional>
#include <map>
#include <string>
#include <vector>
#include "parser/parser.h"
#include "interpreter/aliases.h"
#include "interpreter/eval_error.h"
#include "interpreter/eval_expression.h"
#include "interpreter/context.h"

class Interpreter {
private:
    Parser parser;
    Context env;

    EvaluatedExpression eval(const Expression &expression, Context local_context);
    static EvaluatedExpression eval_leaf(const std::string &value);

    void load_core_lib();

    [[nodiscard]] std::optional<EvaluatedExpression> find_variable(const std::string &name, const Context &local_context) const;

    [[nodiscard]] std::optional<LispFunction> find_function(const std::string &name) const;
    LispFunction find_function(const EvaluatedExpression &applicative) const;

    EvaluatedExpression apply(const EvaluatedExpression &applicative, const std::vector<EvaluatedExpression> &args);

    EvaluatedExpression define(const std::vector<Expression> &input_args, const Context &local_context);
    EvaluatedExpression define_variable(Context &context, const Expression &lhs, const EvaluatedExpression &rhs);
    EvaluatedExpression define_function(const Expression &lhs, Expression rhs);

public:
    explicit Interpreter(Parser p) : parser(p) {
        load_core_lib();
    }

    EvaluatedExpression eval(const std::string& string) {
        return eval(parser.parse(string), {});
    }

    static bool is_define(const EvaluatedExpression &applicative) {
        return applicative.is_symbol() && applicative.get_symbol() == "define";
    }
};

#endif
