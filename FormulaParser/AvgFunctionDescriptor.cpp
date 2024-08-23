#include "AvgFunctionDescriptor.h"
#include "UserFunctions.h"

double AvgFunctionDescriptor::Evaluate(const vector<unique_ptr<TreeItem>>& items) const {
	double sum = 0;
	for (const auto& item : items) {
		sum += UserFunctions::Evaluate(item);
	}

	return sum/items.size();
}
