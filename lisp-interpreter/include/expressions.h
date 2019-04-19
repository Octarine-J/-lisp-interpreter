#ifndef LISP_INTERPRETER_EXPRESSIONS_H
#define LISP_INTERPRETER_EXPRESSIONS_H

#include "tree.h"

using Expression = Tree<std::string>;

std::string toString(const std::shared_ptr<Expression> &expression);

#endif
