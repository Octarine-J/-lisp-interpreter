#ifndef LISP_INTERPRETER_INTERPRETER_H
#define LISP_INTERPRETER_INTERPRETER_H

#include <functional>
#include <map>
#include <string>
#include <vector>
#include "parser/parser.h"
#include "interpreter/eval_error.h"
#include "interpreter/eval_expression.h"

using LispFunctionArgs = std::vector<EvaluatedExpression>;
using LispFunction = std::function<EvaluatedExpression(LispFunctionArgs args)>;

class Interpreter {
private:
    Parser parser;
    std::map<std::string, LispFunction> env;
    std::map<std::string, EvaluatedExpression> variables;

    EvaluatedExpression eval(const Expression &expression);
    static EvaluatedExpression eval_leaf(const std::string &value);

    std::vector<double> to_numeric_args(const std::vector<EvaluatedExpression> &args) const;

    void register_function(const std::string &name, LispFunction function);

    void load_core_lib();

    std::optional<EvaluatedExpression> find_variable(const std::string &name);
    void define_variable(const std::string &name, const EvaluatedExpression &expression);

    std::optional<LispFunction> find_function(const std::string &name);

    EvaluatedExpression apply(const EvaluatedExpression &applicative, const std::vector<EvaluatedExpression> &args);
    EvaluatedExpression define(const std::vector<Expression> &input_args);

public:
    explicit Interpreter(Parser p) : parser(p) {
        load_core_lib();
    }

    EvaluatedExpression eval(const std::string& string) {
        return eval(parser.parse(string));
    }

    static bool is_define(const EvaluatedExpression &applicative) {
        return applicative.is_symbol() && applicative.get_symbol() == "define";
    }
};

#endif
