#pragma once

#include "FunctionDescriptor.h"
#include "UserFunctions.h"

/// <summary>
/// Implements exponentiation. For example: 2^3 = 2*2*2
/// </summary>
class PowFunctionDescriptor : public FunctionDescriptor {
public:
	PowFunctionDescriptor() : FunctionDescriptor(FUNCTION_POW, 2) {
	}

	virtual double Evaluate(const vector<unique_ptr<TreeItem>>& items) const override;
};



