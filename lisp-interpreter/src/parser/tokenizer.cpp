#include "parser/tokenizer.h"

/**
 * Splits a string into tokens.
 * For example, "(+ 3 4)" -> ["(", "+", "3", "4", ")"]
 *
 * @param string - Input string
 * @return a vector of tokens
 */
std::vector<std::string> Tokenizer::tokenize(const std::string &string) const {
    std::vector<std::string> tokens;
    std::string acc;
    for (char c : string) {
        switch (c) {
            case '(':
            case ')':
                if (!acc.empty()) {
                    tokens.push_back(acc);
                    acc.clear();
                }
                tokens.emplace_back(1, c);
                break;
            case ' ':
            case '\n':
            case '\t':
                if (!acc.empty()) {
                    tokens.push_back(acc);
                    acc.clear();
                }
                break;
            default:
                acc += c;
        }
    }

    if (!acc.empty()) {
        tokens.push_back(acc);
    }

    return tokens;
}
