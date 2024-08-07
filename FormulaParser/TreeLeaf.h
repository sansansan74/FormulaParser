#ifndef TREE_LEAF_H
#define TREE_LEAF_H

#include "TreeItem.h"
#include <string>

class TreeLeaf : public TreeItem {
public:
    explicit TreeLeaf(double value) : value_(value) {}

    double GetValue() const {
        return value_;
    }

    virtual std::string ToString() const {
        return std::to_string(value_);
    }

private:
    double value_;
};

#endif // TREE_LEAF_H
