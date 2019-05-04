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
using VariableContext = std::map<std::string, EvaluatedExpression>;

class Interpreter {
private:
    Parser parser;
    std::map<std::string, LispFunction> env;
    VariableContext variables;

    EvaluatedExpression eval(const Expression &expression);
    static EvaluatedExpression eval_leaf(const std::string &value);

    std::vector<double> to_numeric_args(const std::string &function_name, const LispFunctionArgs &args) const;

    void load_core_lib();

    std::optional<EvaluatedExpression> find_variable(const std::string &name);
    static void set_variable(VariableContext &context, const std::string &name, const EvaluatedExpression &expression);

    std::optional<LispFunction> find_function(const std::string &name);
    void register_function(const std::string &name, LispFunction function);

    EvaluatedExpression apply(const EvaluatedExpression &applicative, const std::vector<EvaluatedExpression> &args);

    EvaluatedExpression define(const std::vector<Expression> &input_args);
    EvaluatedExpression define_variable(VariableContext &context, const Expression &lhs, const Expression &rhs);
    EvaluatedExpression define_function(const Expression &lhs, const std::vector<Expression> &args);

    template <class V>
    std::optional<V> find_in_context(const std::map<std::string, V> context, const std::string &name) {
        auto pos = context.find(name);
        if (pos == context.end()) {
            return std::nullopt;
        } else {
            return pos->second;
        }
    }

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
