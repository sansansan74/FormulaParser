#ifndef TREE_OPERATION_H
#define TREE_OPERATION_H

#include "TreeItem.h"
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

class TreeOperation : public TreeItem {
public:
    TreeOperation(const std::string& operation, std::vector<std::unique_ptr<TreeItem>> items = {})
        : operation_(operation), items_(std::move(items)) {}

    TreeOperation(const std::string& operation, std::unique_ptr<TreeItem> op1, std::unique_ptr<TreeItem> op2)
        : operation_(operation) {
        items_.emplace_back(std::move(op1));
        items_.emplace_back(std::move(op2));
    }

    virtual std::string ToString() const {
        std::ostringstream oss;
        oss << operation_ << "(";
        for (size_t i = 0; i < items_.size(); ++i) {
            oss << items_[i]->ToString();
            if (i < items_.size() - 1) {
                oss << ", ";
            }
        }
        oss << ")";
        return oss.str();
    }

    std::vector<std::unique_ptr<TreeItem>>& const GetItems()  { return items_; }
    std::string GetOperation() { return operation_; }

private:
    std::string operation_;
    std::vector<std::unique_ptr<TreeItem>> items_;

};

#endif // TREE_OPERATION_H
