#include <gmock/gmock.h>
#include "parser/expression.h"

using namespace ::testing;

class ExpressionTest : public Test {

};

TEST_F(ExpressionTest, ToStringRoot) {
    Expression expression {"9"};
    EXPECT_THAT(to_string(expression), Eq("9"));
}

TEST_F(ExpressionTest, ToStringSingleExpr) {
    Expression expression({
        Expression {"+"},
        Expression {"3"},
        Expression {"4"}
    });

    EXPECT_THAT(to_string(expression), Eq("Expr< + 3 4 >"));
}

TEST_F(ExpressionTest, ToStringNestedExpr) {
    Expression child({
        Expression {"*"},
        Expression {"5"},
        Expression {"6"}
    });

    Expression parent({
        Expression {"+"},
        child,
        Expression {"4"}
    });

    EXPECT_THAT(to_string(parent), Eq("Expr< + Expr< * 5 6 > 4 >"));
}
