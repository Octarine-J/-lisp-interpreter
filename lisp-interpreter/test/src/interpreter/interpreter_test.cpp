#include <gmock/gmock.h>
#include "interpreter/interpreter.h"

using namespace ::testing;

class InterpreterTest : public Test {
private:
    Interpreter interpreter {Parser {Tokenizer {}}};
public:
    std::string eval(const std::string &string) {
        return interpreter.eval(string).to_string();
    }

    double eval_num(const std::string &string) {
        auto result = interpreter.eval(string);

        EXPECT_TRUE(result.is_number());

        return result.get_number();
    }
};


TEST_F(InterpreterTest, SingleNumber) {
    EXPECT_THAT(eval_num("486"), Eq(486));
}

TEST_F(InterpreterTest, ArithmeticTwoArgs) {
    EXPECT_THAT(eval_num("(+ 137 349)"), Eq(486));
    EXPECT_THAT(eval_num("(+ 2.7 10)"), Eq(12.7));
    EXPECT_THAT(eval_num("(- 1000 400)"), Eq(600));
    EXPECT_THAT(eval_num("(* 5 99)"), Eq(495));
    EXPECT_THAT(eval_num("(/ 10 5)"), Eq(2));
}

TEST_F(InterpreterTest, ArithmeticMultipleArgs) {
    EXPECT_THAT(eval_num("(+ 21 35 12 7)"), Eq(75));
    EXPECT_THAT(eval_num("(* 25 4 12)"), Eq(1200));
}

TEST_F(InterpreterTest, ArithmeticNested) {
    EXPECT_THAT(eval_num("(+ (* 3 5) (- 10 6))"), Eq(19));
    EXPECT_THAT(eval_num("(+ (* 3 (+ (* 2 4) (+ 3 5))) (+ (- 10 7) 6))"), Eq(57));
}

TEST_F(InterpreterTest, DefineVariable) {
    EXPECT_THAT(eval("(define size 2)"), Eq("size"));
    EXPECT_THAT(eval_num("size"), Eq(2));
    EXPECT_THAT(eval_num("(* 5 size)"), Eq(10));
}

TEST_F(InterpreterTest, DefineMultipleVariables) {
    eval("(define pi 3.14159)");
    eval("(define radius 10)");
    EXPECT_THAT(eval_num("(* pi (* radius radius))"), Eq(314.159));

    eval("(define circumference (* 2 pi radius))");
    EXPECT_THAT(eval_num("circumference"), Eq(62.8318));
}

TEST_F(InterpreterTest, DefineNumberShouldFail) {
    EXPECT_THROW(eval("(define 4 2)"), eval_error::ExpectedSymbolicArg);
}

TEST_F(InterpreterTest, DefineTooFewArguments) {
    EXPECT_THROW(eval("(define)"), eval_error::RequiredNumArgsExactly);
    EXPECT_THROW(eval("(define x)"), eval_error::RequiredNumArgsExactly);
}

TEST_F(InterpreterTest, DefineTooManyArguments) {
    EXPECT_THROW(eval("(define x 2 3)"), eval_error::RequiredNumArgsExactly);
}

TEST_F(InterpreterTest, DefineFunction) {
    EXPECT_THAT(eval("(define (square x) (* x x))"), Eq("square"));
    EXPECT_THAT(eval_num("(square 21)"), Eq(441));
}
