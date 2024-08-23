
#pragma once

#ifndef DIVIDE_FUNCTION_DESCRIPTOR_H
#define DIVIDE_FUNCTION_DESCRIPTOR_H

#include "FunctionDescriptor.h"

class DivideFunctionDescriptor : public FunctionDescriptor {
public:
	DivideFunctionDescriptor() : FunctionDescriptor("divide", -1) {
	}

	virtual double Evaluate(const vector<unique_ptr<TreeItem>>& items) const override;
};

#endif // !DIVIDE_FUNCTION_DESCRIPTOR_H