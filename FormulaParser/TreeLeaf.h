#pragma once

/*
`TreeLeaf` - a tree leaf that contains a numerical value.
*/

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

