#include <iostream>
#include <memory>
#include <vector>
#include <stack>
#include <stdexcept>
#include "expressions.h"
#include "parser.h"


std::string eval(const std::string& input) {
    Parser parser;
    return parser.parse(input)->eval()->toString();
}


// int main() {

//     std::cout << eval("(+ 30 5 12)") << std::endl;
//     std::cout << eval("(* (+ 30 5) 12)") << std::endl;

//     return 0;
// }



