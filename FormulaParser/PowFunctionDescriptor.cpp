#include "PowFunctionDescriptor.h"

double PowFunctionDescriptor::Evaluate(const vector<unique_ptr<TreeItem>>& items) const {
	return pow(UserFunctions::Evaluate(items[0]), UserFunctions::Evaluate(items[1]));
}
