#include "DivideFunctionDescriptor.h"
#include "UserFunctions.h"
#include "EvaluateFormulaException.h"

double DivideFunctionDescriptor::Evaluate(const vector<unique_ptr<TreeItem>>& items) const {
	double result = UserFunctions::Evaluate(items[0]);
    for (size_t i = 1; i < items.size(); i++) {
        auto res = UserFunctions::Evaluate(items[i]);
        if (res == 0)
            throw EvaluateFormulaException("Division by zero");

        result /= res;
    }
    return result;
}