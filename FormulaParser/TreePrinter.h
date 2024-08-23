#ifndef TREE_PRINTER_H
#define TREE_PRINTER_H

#include "TreeItem.h"
#include "TreeOperation.h"
#include <sstream>

#include <memory>

using namespace std;

class TreePrinter {
public:
    static string Print(const unique_ptr<TreeItem>& item);

    static void PrintFunctionArguments(TreeOperation* operation, ostringstream& oss);

};

#endif // TREE_PRINTER_H
