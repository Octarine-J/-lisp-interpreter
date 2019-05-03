#include <gmock/gmock.h>
#include "parser/parser.h"

using namespace ::testing;
using token_vec = std::vector<std::string>;

class TokenizerTest : public Test {
private:
    Tokenizer tokenizer;
public:
    token_vec tokenize(const std::string &input) {
        return tokenizer.tokenize(input);
    }
};

TEST_F(TokenizerTest, Empty) {
    token_vec expected;

    EXPECT_THAT(tokenize(""), ContainerEq(expected));
    EXPECT_THAT(tokenize(" "), ContainerEq(expected));
    EXPECT_THAT(tokenize("  "), ContainerEq(expected));

    EXPECT_THAT(tokenize("\n"), ContainerEq(expected));
    EXPECT_THAT(tokenize("  \n  "), ContainerEq(expected));

    EXPECT_THAT(tokenize("\t"), ContainerEq(expected));
    EXPECT_THAT(tokenize("\t\t\n \t"), ContainerEq(expected));
}

TEST_F(TokenizerTest, SingleToken) {
    EXPECT_THAT(tokenize("a"), ContainerEq(token_vec {"a"}));
    EXPECT_THAT(tokenize("test"), ContainerEq(token_vec {"test"}));
    EXPECT_THAT(tokenize("333"), ContainerEq(token_vec {"333"}));
}

TEST_F(TokenizerTest, SeparatorTokens) {
    EXPECT_THAT(tokenize("("), ContainerEq(token_vec {"("}));
    EXPECT_THAT(tokenize("()"), ContainerEq(token_vec {"(", ")"}));
    EXPECT_THAT(tokenize("( )"), ContainerEq(token_vec {"(", ")"}));
    EXPECT_THAT(tokenize(" ( ) "), ContainerEq(token_vec {"(", ")"}));
}

TEST_F(TokenizerTest, Expressions) {
    EXPECT_THAT(tokenize("a b"), ContainerEq(token_vec {"a", "b"}));
    EXPECT_THAT(tokenize("(+ 3 5)"), ContainerEq(token_vec {"(", "+", "3", "5", ")"}));
    EXPECT_THAT(tokenize("(+ 3 (+ 1 5))"), ContainerEq(token_vec {"(", "+", "3", "(", "+", "1", "5", ")", ")"}));
}
