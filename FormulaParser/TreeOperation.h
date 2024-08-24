#pragma once

/*
`TreeOperation` - a tree node representing an expression.
*/

#include "TreeItem.h"
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <memory>

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

