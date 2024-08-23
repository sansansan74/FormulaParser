#pragma once

/*
Converts the expression tree to a human-readable graphical tree drawn using pseudographics.
For example:
1+2 ==>
`-- add
    |-- 1
    `-- 2


(2+3)*(5-3)/2 ==>
`-- divide
    |-- mult
    |   |-- add
    |   |   |-- 2
    |   |   `-- 3
    |   `-- add
    |       |-- 5
    |       `-- -3
    `-- 2
*/

#include "TreeItem.h"
#include "TreeLeaf.h"
#include "TreeOperation.h"
#include <memory>
#include <string>
#include <sstream>
#include <stdexcept>
#include <vector>

using namespace std;

class TreeVisualizer {
public:
    static string Visualize(const unique_ptr<TreeItem>& item);

private:
    static void VisualizeHelper(const unique_ptr<TreeItem>& item, ostringstream& oss, const string& prefix, bool isTail);
};

