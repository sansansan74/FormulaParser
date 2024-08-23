
#pragma once

/*
Implements the multiplication operation.
*/

#include "FunctionDescriptor.h"

class MultFunctionDescriptor : public FunctionDescriptor {
public:
	MultFunctionDescriptor() : FunctionDescriptor(FUNCTION_MULT, -1) {
	}

	virtual double Evaluate(const vector<unique_ptr<TreeItem>>& items) const override;
};
