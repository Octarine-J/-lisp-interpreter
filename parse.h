#ifndef LISP_INTERPRETATOR_PARSE_H
#define LISP_INTERPRETATOR_PARSE_H

#include "expressions.h"

Expression parse(std::vector<std::string> tokens);
std::vector<std::string> tokenize(std::string string);

#endif //LISP_INTERPRETATOR_PARSE_H
