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

using namespace std;

class TreeVisualizer {
public:
    static string Visualize(const unique_ptr<TreeItem>& item);

private:
    static void VisualizeHelper(const unique_ptr<TreeItem>& item, ostringstream& oss, const string& prefix, bool isTail);
};

#endif // TREE_VISUALIZER_H
