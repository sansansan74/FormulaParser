#include "MultFunctionDescriptor.h"
#include "UserFunctions.h"

double MultFunctionDescriptor::Evaluate(const vector<unique_ptr<TreeItem>>& items) const {
	double sum = 1;
	for (const auto& item : items) {
		sum *= UserFunctions::Evaluate(item);
	}

	return sum;
}