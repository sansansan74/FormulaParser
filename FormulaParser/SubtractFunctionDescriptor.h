
#pragma once

#ifndef SUBTRACT_FUNCTION_DESCRIPTOR_H
#define SUBTRACT_FUNCTION_DESCRIPTOR_H

#include "FunctionDescriptor.h"

class SubtractFunctionDescriptor : public FunctionDescriptor {
public:
	SubtractFunctionDescriptor() : FunctionDescriptor("subtract", -1) {
	}

	virtual double Evaluate(const vector<unique_ptr<TreeItem>>& items) const override;
};

#endif // !SUBTRACT_FUNCTION_DESCRIPTOR_H