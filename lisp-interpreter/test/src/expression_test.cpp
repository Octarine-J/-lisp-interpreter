#include <gtest/gtest.h>
#include "expression.h"

class ExpressionTest : public testing::Test {

};

TEST_F(ExpressionTest, ToStringRoot) {
    Expression expression {"9"};
    ASSERT_EQ("9", to_string(expression));
}

TEST_F(ExpressionTest, ToStringSingleExpr) {
    Expression expression({
        Expression {"+"},
        Expression {"3"},
        Expression {"4"}
    });

    ASSERT_EQ("Expr< + 3 4 >", to_string(expression));
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

    ASSERT_EQ("Expr< + Expr< * 5 6 > 4 >", to_string(parent));
}
