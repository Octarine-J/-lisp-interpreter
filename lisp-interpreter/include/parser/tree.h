#ifndef LISP_INTERPRETER_TREE_H
#define LISP_INTERPRETER_TREE_H

#include <functional>
#include <vector>

template <class T>
class Tree {
private:
    T value;
    std::vector<Tree> children;
public:
    Tree() = default;

    explicit Tree(T val) : value(val) {}

    Tree(const std::initializer_list<Tree> &nodes) {
        add_children(nodes);
    }

    const std::vector<Tree>& get_children() const {
        return children;
    }

    T get_value() const {
        return value;
    }

    void add_child(const Tree &node) {
        children.push_back(node);
    }

    void add_children(std::initializer_list<Tree> nodes) {
        for (const auto &node : nodes) {
            add_child(node);
        }
    }

    bool is_leaf() const {
        return children.empty();
    }

    template <class V>
    V dfs_fold(const std::function<V(const V &acc, const Tree &node)> &f,
               const V &default_value) const {
        V result = default_value;
        return dfs_fold(this, f, result);
    }

private:
    template <class V>
    V dfs_fold(const Tree *root,
               const std::function<V(const V &acc, const Tree &node)> &f,
               V &acc) const {
        acc = f(acc, *root);

        for (const auto &node : root->children) {
            acc = dfs_fold(&node, f, acc);
        }

        return acc;
    }
};

#endif
