#include <gmock/gmock.h>
#include "parser.h"

class ParserTest : public testing::Test {
private:
    Parser parser;
public:
    std::string parse(const std::string &string) {
        return to_string(parser.parse(string));
    }
};

TEST_F(ParserTest, ParseSingleNumber) {
    ASSERT_EQ("333", parse("333"));
}

TEST_F(ParserTest, TestParseExpressions) {
    ASSERT_EQ(parse("(+ 30 5 12)"), "Expr< + 30 5 12 >");

    ASSERT_EQ(parse("(* (+ 30 5) 12)"), "Expr< * Expr< + 30 5 > 12 >");
    ASSERT_EQ(parse("(* 30 (+ 5 12))"), "Expr< * 30 Expr< + 5 12 > >");

    ASSERT_EQ(parse("(* (+ (- 10 2 1) 30) 12)"), "Expr< * Expr< + Expr< - 10 2 1 > 30 > 12 >");

    ASSERT_EQ(parse("(* (+ 2.3 0.2) 2)"), "Expr< * Expr< + 2.3 0.2 > 2 >");
}

TEST_F(ParserTest, TestParseEmpty) {
    ASSERT_THROW(parse(""), parser_error);
    ASSERT_THROW(parse("()"), parser_error);
    ASSERT_THROW(parse("( )"), parser_error);
    ASSERT_THROW(parse("(    )"), parser_error);
}

TEST_F(ParserTest, TestParseEmptySubexpression) {
    ASSERT_THROW(parse("(+ 3 ())"), parser_error);
    ASSERT_THROW(parse("(+ () 3)"), parser_error);
    ASSERT_THROW(parse("(+ 3 4 5 (* 2 (+ 3 ()) ) )"), parser_error);
}

TEST_F(ParserTest, TestParseUnmatchedClosedParenthesis) {
    ASSERT_THROW(parse(")"), parser_error);
    ASSERT_THROW(parse("())"), parser_error);
    ASSERT_THROW(parse("(+ 3 5) )"), parser_error);
    ASSERT_THROW(parse("(+ (+ 3 5) ) 4)"), parser_error);
}

TEST_F(ParserTest, TestParseUnmatchedOpenParenthesis) {
    ASSERT_THROW(parse("("), parser_error);
    ASSERT_THROW(parse("(()"), parser_error);
    ASSERT_THROW(parse("(+ 3 5"), parser_error);
    ASSERT_THROW(parse("(+ (+ 3 5) ) 4"), parser_error);
}
