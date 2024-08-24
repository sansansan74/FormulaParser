#include "SubtractFunctionDescriptor.h"
#include "UserFunctions.h"

double SubtractFunctionDescriptor::Evaluate(const vector<unique_ptr<TreeItem>>& items) const {
    // 8-2-4-1
	double result = UserFunctions::Evaluate(items[0]);
    for (size_t i = 1; i < items.size(); i++) {
        auto res = UserFunctions::Evaluate(items[i]);

        result -= res;
    }
    return result;
}