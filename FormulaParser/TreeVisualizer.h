#ifndef TREE_VISUALIZER_H
#define TREE_VISUALIZER_H

#include "TreeItem.h"
#include "TreeLeaf.h"
#include "TreeOperation.h"
#include <memory>
#include <string>
#include <sstream>
#include <stdexcept>
#include <vector>

class TreeVisualizer {
public:
    static std::string Visualize(const std::unique_ptr<TreeItem>& item) {
        std::ostringstream oss;
        VisualizeHelper(item, oss, "", true);
        return oss.str();
    }

private:
    static void VisualizeHelper(const std::unique_ptr<TreeItem>& item, std::ostringstream& oss, const std::string& prefix, bool isTail) {
        if (const TreeLeaf* leaf = dynamic_cast<const TreeLeaf*>(item.get())) {
            oss << prefix << (isTail ? "`-- " : "|-- ") << leaf->GetValue() << "\n";
            return;
        }
        
        if (TreeOperation* operation = dynamic_cast<TreeOperation*>(item.get())) {
            oss << prefix << (isTail ? "`-- " : "|-- ") << operation->GetOperation() << "\n";
            
            const auto& items = operation->GetItems();
            for (size_t i = 0; i + 1 < items.size(); ++i) {
                VisualizeHelper(items[i], oss, prefix + (isTail ? "    " : "|   "), false);
            }
            if (!items.empty()) {
                VisualizeHelper(items.back(), oss, prefix + (isTail ? "    " : "|   "), true);
            }
            
            return;
        }

        throw std::invalid_argument("Unknown TreeItem type");
    }
};

#endif // TREE_VISUALIZER_H
