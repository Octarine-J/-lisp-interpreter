#ifndef LISP_INTERPRETER_CONTEXT_H
#define LISP_INTERPRETER_CONTEXT_H

#include <optional>

class Context {
private:
    std::map<std::string, LispFunction> functions;
    std::map<std::string, EvaluatedExpression> variables;

    template <class V>
    std::optional<V> find_in_context(const std::map<std::string, V> &ctx, const std::string &name) const {
        auto pos = ctx.find(name);
        if (pos == ctx.end()) {
            return std::nullopt;
        } else {
            return pos->second;
        }
    }

public:
    void set_variable(const std::string &name, const EvaluatedExpression &expression) {
        variables.insert(std::make_pair(name, expression));
    }

    void register_function(const std::string &name, LispFunction function) {
        functions.insert(std::make_pair(name, function));
    }

    std::optional<EvaluatedExpression> find_variable(const std::string &name) const {
        return find_in_context(variables, name);
    }

    std::optional<LispFunction> find_function(const std::string &name) const {
        return find_in_context(functions, name);
    }

};


#endif
