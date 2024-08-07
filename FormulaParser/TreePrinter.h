#ifndef TREE_PRINTER_H
#define TREE_PRINTER_H

#include "TreeItem.h"
#include "TreeLeaf.h"
#include "TreeOperation.h"
#include <sstream>
#include <string>
#include <stdexcept>
#include <memory>

class TreePrinter {
public:
    static std::string Print(const std::unique_ptr<TreeItem>& item) {
        if (auto leaf = dynamic_cast<const TreeLeaf*>(item.get())) {
            return std::to_string(leaf->GetValue());
        }

        if (auto operation = dynamic_cast<TreeOperation*>(item.get())) {
            std::ostringstream oss;
            
            oss << operation->GetOperation() << "(";

            PrintFunctionArguments(operation, oss);

            oss << ")";
            return oss.str();
        }

        throw std::invalid_argument("Unknown TreeItem type");
    }

    static void PrintFunctionArguments(TreeOperation* operation, std::ostringstream& oss)
    {
        auto& args = operation->GetItems();
        for (size_t i = 0; i < args.size(); ++i) {
            oss << Print(args[i]);
            if (i < args.size() - 1) {
                oss << ",";
            }
        }
    }

};

#endif // TREE_PRINTER_H
