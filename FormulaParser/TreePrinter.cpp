#include "TreePrinter.h"
#include "TreeLeaf.h"
#include "EvaluateFormulaException.h"
#include <string>
#include <stdexcept>

string TreePrinter::Print(const unique_ptr<TreeItem>& item) {
    if (auto leaf = dynamic_cast<const TreeLeaf*>(item.get())) {
        return to_string(leaf->GetValue());
    }

    if (auto operation = dynamic_cast<TreeOperation*>(item.get())) {
        ostringstream oss;

        oss << operation->GetOperation() << "(";

        PrintFunctionArguments(operation, oss);

        oss << ")";
        return oss.str();
    }

    throw EvaluateFormulaException("Unknown TreeItem type");
}

void TreePrinter::PrintFunctionArguments(TreeOperation* operation, ostringstream& oss)
{
    auto& args = operation->GetItems();
    for (size_t i = 0; i < args.size(); ++i) {
        oss << Print(args[i]);
        if (i < args.size() - 1) {
            oss << ",";
        }
    }
}
