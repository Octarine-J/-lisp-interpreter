#include <gmock/gmock.h>
#include "parser.h"

using namespace ::testing;

class ParserTest : public Test {
private:
    Parser parser {Tokenizer {}};
public:
    std::string parse(const std::string &input) {
        return to_string(parser.parse(input));
    }

    void expect_error(const std::string &input, ParseErrorType expected_error_type) {
        EXPECT_THROW({
            try {
                parse(input);
            }
            catch(const parser_error& e) {
                EXPECT_STREQ(e.what(), e.get_description(expected_error_type));
                throw;
            }
         }, parser_error);
    }
};

TEST_F(ParserTest, SingleNumber) {
    EXPECT_THAT(parse("333"), Eq("333"));
}

TEST_F(ParserTest, SimpleExpression) {
    EXPECT_THAT(parse("(+ 30)"), Eq("Expr< + 30 >"));
    EXPECT_THAT(parse("(+ 30 5)"), Eq("Expr< + 30 5 >"));
    EXPECT_THAT(parse("(+ 30 5 12)"), Eq("Expr< + 30 5 12 >"));
}

TEST_F(ParserTest, NestedExpressions) {
    EXPECT_THAT(parse("(* (+ 30 5) 12)"), Eq("Expr< * Expr< + 30 5 > 12 >"));
    EXPECT_THAT(parse("(* 30 (+ 5 12))"), Eq("Expr< * 30 Expr< + 5 12 > >"));

    EXPECT_THAT(parse("(* (+ (- 10 2 1) 30) 12)"), Eq("Expr< * Expr< + Expr< - 10 2 1 > 30 > 12 >"));

    EXPECT_THAT(parse("(* (+ 2.3 0.2) 2)"), Eq("Expr< * Expr< + 2.3 0.2 > 2 >"));
}

TEST_F(ParserTest, EmptyInput) {
    expect_error("", ParseErrorType::EmptyExpression);
}

TEST_F(ParserTest, EmptyExpression) {
    expect_error("()", ParseErrorType::EmptyExpression);
    expect_error("( )", ParseErrorType::EmptyExpression);
    expect_error("(    )", ParseErrorType::EmptyExpression);
}

TEST_F(ParserTest, EmptyNestedExperession) {
    expect_error("(())", ParseErrorType::EmptyExpression);
    expect_error("(+ 3 ())", ParseErrorType::EmptyExpression);
    expect_error("(+ () 3)", ParseErrorType::EmptyExpression);
    expect_error("(+ 3 4 5 (* 2 (+ 3 ()) ) )", ParseErrorType::EmptyExpression);
}

TEST_F(ParserTest, EmptyExperessionParenthesesMismatch) {
    expect_error("())", ParseErrorType::EmptyExpression);
    expect_error("(()", ParseErrorType::EmptyExpression);
}

TEST_F(ParserTest, UnmatchedClosedParenthesis) {
    expect_error(")", ParseErrorType::UnmatchedClosedParenthesis);
    expect_error("))", ParseErrorType::UnmatchedClosedParenthesis);
    expect_error("(+ 3 5) )", ParseErrorType::UnmatchedClosedParenthesis);
}

TEST_F(ParserTest, TestParseUnmatchedOpenParenthesis) {
    expect_error("(", ParseErrorType::PrematureEndOfExpression);
    expect_error("(+ 3 5", ParseErrorType::PrematureEndOfExpression);
    expect_error("(+ (* 3 5) 10", ParseErrorType::PrematureEndOfExpression);
}

TEST_F(ParserTest, OutsideTokens) {
    expect_error("4 (", ParseErrorType::TokenOutsideExpression);
    expect_error("+ (+ 3 4)", ParseErrorType::TokenOutsideExpression);
    expect_error("(+ 3 4) 5", ParseErrorType::TokenOutsideExpression);
    expect_error("(+ (+ 3 5) ) 4)", ParseErrorType::TokenOutsideExpression);
}

TEST_F(ParserTest, NoTopLevelExpression) {
    expect_error("(+ 3 4) 9", ParseErrorType::TokenOutsideExpression);
    expect_error("(+ 3 4) (+ 3 5)", ParseErrorType::TokenOutsideExpression);
    expect_error("(+ 3 4) (+ 3 5) (* 2 3)", ParseErrorType::TokenOutsideExpression);
}
