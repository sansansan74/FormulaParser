
#pragma once

/*
Implements the division operation.
*/

#include "FunctionDescriptor.h"

class DivideFunctionDescriptor : public FunctionDescriptor {
public:
	DivideFunctionDescriptor() : FunctionDescriptor(FUNCTION_DIVIDE, -1) {
	}

	virtual double Evaluate(const vector<unique_ptr<TreeItem>>& items) const override;
};
