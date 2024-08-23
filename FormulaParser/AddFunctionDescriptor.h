
#pragma once


/*
Implements the addition operation.
*/

#include "FunctionDescriptor.h"

class AddFunctionDescriptor : public FunctionDescriptor {
public:
	AddFunctionDescriptor() : FunctionDescriptor(FUNCTION_ADD, -1) {
	}

	virtual double Evaluate(const vector<unique_ptr<TreeItem>>& items) const override;
};
