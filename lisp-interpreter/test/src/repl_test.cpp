#include <gmock/gmock.h>
#include "repl.h"

using namespace ::testing;

class ReplTest : public Test {

};

TEST_F(ReplTest, IsCommandWhitespace) {
    EXPECT_FALSE(is_command(""));
    EXPECT_FALSE(is_command(" "));
    EXPECT_FALSE(is_command("\n"));
}

TEST_F(ReplTest, IsCommandSingleColon) {
    EXPECT_FALSE(is_command(":"));
}

TEST_F(ReplTest, IsCommandValid) {
    EXPECT_TRUE(is_command(":t"));
    EXPECT_TRUE(is_command(":test"));
}

TEST_F(ReplTest, AsCommandValid) {
    EXPECT_THAT(as_command(":t"), StrEq("t"));
    EXPECT_THAT(as_command(":test"), StrEq("test"));
}

TEST_F(ReplTest, ShouldExitFalse) {
    EXPECT_FALSE(should_exit(""));
    EXPECT_FALSE(should_exit("\n"));
    EXPECT_FALSE(should_exit(":"));
    EXPECT_FALSE(should_exit(":q"));
    EXPECT_FALSE(should_exit("command"));
}

TEST_F(ReplTest, ShouldExitTrue) {
    EXPECT_TRUE(should_exit("q"));
    EXPECT_TRUE(should_exit("quit"));
}
