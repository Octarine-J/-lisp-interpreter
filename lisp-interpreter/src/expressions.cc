#include "expressions.h"

std::string toString(const std::shared_ptr<Expression> &expression) {
    if (expression->is_leaf()) {
        return expression->get_value();
    }

    std::string result = "Expr< ";

    for (const auto &child : expression->get_children()) {
        result += toString(child) + " ";
    }

    result += ">";
    return result;
}
