#include "gmock/gmock.h"
#include "parser.h"

class ParserTest : public testing::Test {

};

TEST_F(ParserTest, TestParseExpressions) {
    ASSERT_EQ(parse(tokenize("(+ 30 5 12)")).toString(), "Expr< + 30 5 12 >");

    ASSERT_EQ(parse(tokenize("(* (+ 30 5) 12)")).toString(), "Expr< * Expr< + 30 5 > 12 >");
    ASSERT_EQ(parse(tokenize("(* 30 (+ 5 12))")).toString(), "Expr< * 30 Expr< + 5 12 > >");

    ASSERT_EQ(parse(tokenize("(* (+ (- 10 2 1) 30) 12)")).toString(), "Expr< * Expr< + Expr< - 10 2 1 > 30 > 12 >");
}
