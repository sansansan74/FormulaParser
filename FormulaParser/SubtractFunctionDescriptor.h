
#pragma once

/*
Implements the subtraction operation.
*/

#include "FunctionDescriptor.h"

class SubtractFunctionDescriptor : public FunctionDescriptor {
public:
	SubtractFunctionDescriptor() : FunctionDescriptor(FUNCTION_SUBTRACT, -1) {
	}

	virtual double Evaluate(const vector<unique_ptr<TreeItem>>& items) const override;
};
