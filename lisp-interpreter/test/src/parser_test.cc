#include "gmock/gmock.h"
#include "parser.h"

class ParserTest : public testing::Test {
private:
    Parser parser;
public:
    std::string parse(const std::string &string) {
        return parser.parse(string)->toString();
    }
};

TEST_F(ParserTest, TestParseExpressions) {
    ASSERT_EQ(parse("(+ 30 5 12)"), "Expr< + 30 5 12 >");

    ASSERT_EQ(parse("(* (+ 30 5) 12)"), "Expr< * Expr< + 30 5 > 12 >");
    ASSERT_EQ(parse("(* 30 (+ 5 12))"), "Expr< * 30 Expr< + 5 12 > >");

    ASSERT_EQ(parse("(* (+ (- 10 2 1) 30) 12)"), "Expr< * Expr< + Expr< - 10 2 1 > 30 > 12 >");

    ASSERT_EQ(parse("(* (+ 2.3 0.2) 2)"), "Expr< * Expr< + 2.3 0.2 > 2 >");
}
