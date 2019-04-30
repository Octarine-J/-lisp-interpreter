#include <gtest/gtest.h>
#include "tree.h"

class TreeTest : public testing::Test {

};

TEST_F(TreeTest, TestSingleNode) {
    Tree<int> tree {3};
    ASSERT_EQ(3, tree.get_value());
}
