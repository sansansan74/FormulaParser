#include "TreeVisualizer.h"
#include "EvaluateFormulaException.h"

string TreeVisualizer::Visualize(const unique_ptr<TreeItem>& item) {
    ostringstream oss;
    VisualizeHelper(item, oss, "", true);
    return oss.str();
}

inline void TreeVisualizer::VisualizeHelper(const unique_ptr<TreeItem>& item, ostringstream& oss, const string& prefix, bool isTail) {
    auto prefix_right = prefix + (isTail ? "`-- " : "|-- ");

    if (const TreeLeaf* leaf = dynamic_cast<const TreeLeaf*>(item.get())) {
        oss << prefix_right << leaf->GetValue() << "\n";
        return;
    }

    if (TreeOperation* operation = dynamic_cast<TreeOperation*>(item.get())) {
        oss << prefix_right << operation->GetOperation() << "\n";

        auto prefix_new = prefix + (isTail ? "    " : "|   ");
        const auto& items = operation->GetItems();

        for (size_t i = 0; i + 1 < items.size(); ++i) {
            VisualizeHelper(items[i], oss, prefix_new, false);
        }

        if (!items.empty()) {
            VisualizeHelper(items.back(), oss, prefix_new, true);
        }

        return;
    }

    throw EvaluateFormulaException("Unknown TreeItem type");
}
