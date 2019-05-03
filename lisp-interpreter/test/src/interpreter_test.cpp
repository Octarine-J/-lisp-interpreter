#include <gmock/gmock.h>
#include "interpreter.h"

using namespace ::testing;

class InterpreterTest : public Test {
private:
    Interpreter interpreter {Parser {Tokenizer {}}};
public:
    std::string eval(const std::string &string) {
        return interpreter.eval(string).get_value();
    }

    double eval_num(const std::string &string) {
        return std::stod(eval(string));
    }
};


TEST_F(InterpreterTest, SingleNumber) {
    EXPECT_THAT(eval_num("486"), Eq(486));
}

TEST_F(InterpreterTest, TestEval) {
    EXPECT_THAT(eval_num("(+ 30 5 12)"), Eq(47));
    EXPECT_THAT(eval_num("(* (+ 2.3 0.2) 2)"), Eq(5));
}
