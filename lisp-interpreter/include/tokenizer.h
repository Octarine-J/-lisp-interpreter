#ifndef LISP_INTERPRETER_TOKENIZER_H
#define LISP_INTERPRETER_TOKENIZER_H

#include <string>
#include <vector>

class Tokenizer {
public:
    std::vector<std::string> tokenize(const std::string &string) const;
};

#endif
