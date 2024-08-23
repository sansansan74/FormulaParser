#pragma once

/*
Converts the expression tree to a string representation in a functional style.
For example:
    1+2 ==> add(1,2)
    (2+3)*(5-3)/2 ==> divide(mult(add(2.000000,3.000000),add(5.000000,-3.000000)),2.000000)
*/

#include "TreeItem.h"
#include "TreeOperation.h"
#include <sstream>

#include <memory>

using namespace std;

class TreePrinter {
public:
    static string Print(const unique_ptr<TreeItem>& item);

private:
    static void PrintFunctionArguments(TreeOperation* operation, ostringstream& oss);
};

