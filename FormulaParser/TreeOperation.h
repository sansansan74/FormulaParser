#ifndef TREE_OPERATION_H
#define TREE_OPERATION_H

#include "TreeItem.h"
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

class TreeOperation : public TreeItem {
public:
    TreeOperation(const string& operation, vector<unique_ptr<TreeItem>> items = {})
        : operation_(operation), items_(move(items)) {}

    TreeOperation(const string& operation, unique_ptr<TreeItem> op1, unique_ptr<TreeItem> op2);

    virtual string ToString() const;

    vector<unique_ptr<TreeItem>>& const GetItems()  { return items_; }
    string GetOperation() { return operation_; }

private:
    string operation_;
    vector<unique_ptr<TreeItem>> items_;

};

#endif // TREE_OPERATION_H
