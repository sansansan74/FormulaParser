#include "TreeOperation.h"

TreeOperation::TreeOperation(const string& operation, unique_ptr<TreeItem> op1, unique_ptr<TreeItem> op2)
    : operation_(operation) {
    items_.emplace_back(move(op1));
    items_.emplace_back(move(op2));
}

string TreeOperation::ToString() const {
    ostringstream oss;
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
