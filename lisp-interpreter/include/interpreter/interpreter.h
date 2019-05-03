#ifndef LISP_INTERPRETER_INTERPRETER_H
#define LISP_INTERPRETER_INTERPRETER_H

#include <functional>
#include <map>
#include <string>
#include <vector>
#include "parser/parser.h"
#include "interpreter/eval_error.h"

class Interpreter {
private:
    Parser parser;
    std::map<std::string, std::function<Expression(std::vector<Expression> args)>> env;
    std::map<std::string, Expression> variables;

    std::vector<double> to_numeric_args(const std::vector<Expression> &args) const;

    void register_function(const std::string &name, std::function<Expression(std::vector<Expression> args)> function);

    void load_core_lib();

public:
    explicit Interpreter(Parser p) : parser(p) {
        load_core_lib();
    }

    Expression eval(const std::string& string) {
        return eval(parser.parse(string));
    }

    Expression eval(const Expression &expression) {
        auto value = expression.get_value();
        auto children = expression.get_children();

        if (expression.is_leaf()) {
            auto var_search_result = variables.find(expression.get_value());
            if (var_search_result != variables.cend()) {
                return var_search_result->second;
            } else {
                return expression;
            }
        }

        auto applicative = eval(children[0]);

        if (is_define(applicative)) {
            return define(children);
        } else {
            std::vector<Expression> args;
            for (int i = 1; i < children.size(); ++i) {
                args.push_back(eval(children[i]));
            }

            return apply(applicative, args);
        }
    }

    static bool is_define(const Expression &applicative) {
        return applicative.get_value() == "define";
    }

    Expression define(const std::vector<Expression> &input_args) {
        if (input_args.size() != 3) {
            // (define what expr)
            throw eval_error(EvalErrorType::RequiredNArgsExactly, {"define", "2"});
        }

        auto definition = input_args[1];
        if (!definition.is_leaf()) {
            throw eval_error(EvalErrorType::ExpectedSingleToken);
        }

        this->variables.insert(std::make_pair(definition.get_value(), input_args[2]));

//        register_function(definition.get_value(), [this](std::vector<Expression> args) {
//            return eval(args[2]);
//        });

        return definition;
    }

    Expression apply(const Expression &applicative, const std::vector<Expression> &args) {
        auto pos = env.find(applicative.get_value());
        if (pos == env.end()) {
            throw std::runtime_error("unknown applicative: " + applicative.get_value());
        }

        return pos->second(args);
    }

};

#endif
