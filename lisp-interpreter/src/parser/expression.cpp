#include "parser/expression.h"

std::string to_string(const Expression &expression) {
    if (expression.is_leaf()) {
        return expression.get_value();
    }

    std::string result = "Expr< ";

    for (const auto &child : expression.get_children()) {
        result += to_string(child) + " ";
    }

    result += ">";
    return result;
}
