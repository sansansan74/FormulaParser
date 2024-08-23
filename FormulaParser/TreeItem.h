#ifndef ITREEITEM_H
#define ITREEITEM_H

#include <string>

class TreeItem {
public:
    virtual std::string ToString() const = 0;
    virtual ~TreeItem() = default;
};

#endif // ITREEITEM_H
