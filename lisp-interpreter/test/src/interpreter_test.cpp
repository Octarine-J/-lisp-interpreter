#include <gmock/gmock.h>
#include "interpreter.h"

class InterpreterTest : public testing::Test {
private:
    Interpreter interpreter = Interpreter(Parser());
public:
    std::string eval(const std::string &string) {
        return interpreter.eval(string).get_value();
    }

    double eval_num(const std::string &string) {
        return std::stod(eval(string));
    }
};


TEST_F(InterpreterTest, SingleNumber) {
    ASSERT_EQ(486, eval_num("486"));
}

TEST_F(InterpreterTest, TestEval) {
    ASSERT_EQ(eval_num("(+ 30 5 12)"), 47);
    ASSERT_EQ(eval_num("(* (+ 2.3 0.2) 2)"), 5);
}
