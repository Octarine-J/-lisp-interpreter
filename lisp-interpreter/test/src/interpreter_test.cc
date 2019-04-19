#include "gmock/gmock.h"
#include "interpreter.h"

class InterpreterTest : public testing::Test {
private:
    Interpreter interpreter = Interpreter(Parser());
public:
    std::string eval(const std::string &string) {
        return interpreter.eval(string)->get_value();
    }

    double evalNum(const std::string &string) {
        return std::stod(eval(string));
    }
};

TEST_F(InterpreterTest, TestEval) {
    ASSERT_EQ(evalNum("(+ 30 5 12)"), 47);
    ASSERT_EQ(evalNum("(* (+ 2.3 0.2) 2)"), 5);
}
