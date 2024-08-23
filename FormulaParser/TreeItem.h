#pragma once

/*
`TreeItem` is the base class for the hierarchy of the tree representation of an expression.
It has the following descendants:
- `TreeLeaf` - a tree leaf that contains a numerical value.
- `TreeOperation` - a tree node representing an expression.
*/

#include <string>

class TreeItem {
public:
    virtual std::string ToString() const = 0;
    virtual ~TreeItem() = default;
};

