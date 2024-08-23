#pragma once

#include "FunctionDescriptor.h"

class AvgFunctionDescriptor : public FunctionDescriptor {
public:
	AvgFunctionDescriptor() : FunctionDescriptor(FUNCTION_AVG, -1) {
	}

	 virtual double Evaluate(const vector<unique_ptr<TreeItem>>& items) const override;
};




