#ifndef LISP_INTERPRETER_REPL_H
#define LISP_INTERPRETER_REPL_H

#include <string>

bool is_command(const std::string &input) {
    return (input.size() >= 2) && input[0] == ':';
}

std::string as_command(const std::string &input) {
    return std::string(input.cbegin() + 1, input.cend());
}

bool should_exit(const std::string &command) {
    return command == "q" || command == "quit";
}

#endif
