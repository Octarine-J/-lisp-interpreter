#include <iostream>
#include <memory>
#include <vector>
#include <stack>
#include <stdexcept>
#include "expressions.h"
#include "parse.h"


std::string eval(const std::string& input);
void assertEquals(const std::string &expected, const std::string &actual);


int main() {
    std::string input = "(+ 30 5 12)";
    assertEquals("Expr< + 30 5 12 >", parse(tokenize("(+ 30 5 12)")).toString());
    assertEquals("Expr< * Expr< + 30 5 > 12 >", parse(tokenize("(* (+ 30 5) 12)")).toString());

    std::cout << eval("(+ 30 5 12)") << std::endl;
    std::cout << eval("(* (+ 30 5) 12)") << std::endl;

    return 0;
}


void assertEquals(const std::string &expected, const std::string &actual) {
    if (expected != actual) {
        std::cerr << "Expected: '" << expected << "', but was: '" << actual << "'\n";
    }
}


std::string eval(const std::string& input) {
    return parse(tokenize(input)).eval()->toString();
}
