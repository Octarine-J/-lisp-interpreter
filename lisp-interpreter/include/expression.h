#ifndef LISP_INTERPRETER_EXPRESSIONS_H
#define LISP_INTERPRETER_EXPRESSIONS_H

#include "tree.h"

using Expression = Tree<std::string>;

std::string to_string(const Expression &expression);

#endif
