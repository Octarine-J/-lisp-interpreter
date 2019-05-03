#include <gmock/gmock.h>
#include "tree.h"

using namespace ::testing;

class TreeTest : public Test {

public:
    // used to test dfs_fold
    static std::string to_string(const std::string &acc, const Tree<int> &node) {
        return acc + std::to_string(node.get_value()) + " ";
    }
};

TEST_F(TreeTest, TestCreateEmpty) {
    Tree<int> tree;
    EXPECT_TRUE(tree.is_leaf());
}

TEST_F(TreeTest, TestCreateSingleNode) {
    Tree<int> tree {3};
    EXPECT_THAT(tree.get_value(), Eq(3));
    EXPECT_TRUE(tree.is_leaf());
}

TEST_F(TreeTest, TestCreateSingleLayer) {
    Tree<int> tree;
    tree.add_child(Tree<int> {3});
    tree.add_child(Tree<int> {4});

    EXPECT_FALSE(tree.is_leaf());

    auto children = tree.get_children();
    EXPECT_THAT(children[0].get_value(), Eq(3));
    EXPECT_THAT(children[1].get_value(), Eq(4));
}

TEST_F(TreeTest, TestCreateTwoLayers) {
    Tree<int> first_node;
    first_node.add_child(Tree<int> {2});
    first_node.add_child(Tree<int> {5});

    Tree<int> tree;
    tree.add_child(first_node);

    EXPECT_FALSE(tree.is_leaf());

    auto children = tree.get_children();
    auto first_child = children[0];

    EXPECT_FALSE(first_child.is_leaf());

    auto grandchildren = first_child.get_children();
    auto first_grandchild = grandchildren[0];
    auto second_grandchild = grandchildren[1];

    EXPECT_TRUE(first_grandchild.is_leaf());
    EXPECT_THAT(first_grandchild.get_value(), Eq(2));
    EXPECT_TRUE(second_grandchild.is_leaf());
    EXPECT_THAT(second_grandchild.get_value(), Eq(5));
}

TEST_F(TreeTest, TestDFS) {
    Tree<int> first_node {4};
    first_node.add_child(Tree<int>{2});
    first_node.add_child(Tree<int>{5});

    Tree<int> second_node {3};
    second_node.add_child(Tree<int>{8});
    second_node.add_child(Tree<int>{7});

    Tree<int> tree {9};
    tree.add_child(first_node);
    tree.add_child(second_node);

    auto result = tree.dfs_fold<std::string>(to_string, std::string {});

    EXPECT_THAT(result, Eq("9 4 2 5 3 8 7 "));
}

TEST_F(TreeTest, TestDFSSingleNode) {
    Tree<int> tree {4};

    auto result = tree.dfs_fold<std::string>(to_string, std::string {});

    EXPECT_THAT(result, Eq("4 "));
}
