#include <iostream>
#include "repl.h"
#include "interpreter/interpreter.h"


int main() {
    Interpreter interpreter {Parser {Tokenizer {}}};

    while (true) {
        std::string input;
        std::getline(std::cin, input);

        if (input.empty()) {
            continue;
        }

        if (is_command(input)) {
            auto command = as_command(input);

            if (should_exit(command)) {
                break;
            }
        }

        try {
            std::cout << interpreter.eval(input).to_string();
        } catch (std::runtime_error &e) {
            std::cout << e.what();
        }

        std::cout << std::endl;
    }

    return 0;
}
