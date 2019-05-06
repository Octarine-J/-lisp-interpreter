#ifndef LISP_INTERPRETER_ALIASES_H
#define LISP_INTERPRETER_ALIASES_H

#include "interpreter/eval_expression.h"

using LispFunctionArgs = std::vector<EvaluatedExpression>;
using LispFunction = std::function<EvaluatedExpression(LispFunctionArgs args)>;

#endif
