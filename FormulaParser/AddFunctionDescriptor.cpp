#include "AddFunctionDescriptor.h"
#include "UserFunctions.h"

double AddFunctionDescriptor::Evaluate(const vector<unique_ptr<TreeItem>>& items) const {
	double sum = 0;
	for (const auto& item : items) {
		sum += UserFunctions::Evaluate(item);
	}

	return sum;
}