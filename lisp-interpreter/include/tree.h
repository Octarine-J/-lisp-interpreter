#ifndef LISPINTERPRETER_TREE_H
#define LISPINTERPRETER_TREE_H

#include <memory>
#include <string>
#include <vector>

template <class T>
class Tree : public std::enable_shared_from_this<Tree<T>> {
private:
    T value;
    std::vector<std::shared_ptr<Tree>> children;
public:
    Tree() = default;

    Tree(T val) : value(val) {}

    decltype(children) get_children() const {
        return children;
    }

    decltype(value) get_value() const {
        return value;
    }

    void add_child(const std::shared_ptr<Tree> &node) {
        children.push_back(node);
    }

    bool is_leaf() const {
        return children.empty();
    }

    T dfs(const std::function<T(const T &acc, const std::shared_ptr<Tree> &node)> &f,
          const std::function<T(const T &acc)> &onLevel,
          const T &default_value) const {
        T result = default_value;
        return dfs(this->shared_from_this(), f, onLevel, result);
    }

private:
    T dfs(const std::shared_ptr<const Tree> &root,
          const std::function<T(const T &acc, const std::shared_ptr<Tree> &node)> &f,
          const std::function<T(const T &acc)> &onLevel,
          T &acc) const {

        for (const auto &node : root->children) {
            if (node->is_leaf()) {
                acc = f(acc, node);
            } else {
                acc = dfs(node, f, onLevel, acc);
            }
        }
        return onLevel(acc);
    }
};

#endif
