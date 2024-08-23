
#pragma once

#ifndef ADD_FUNCTION_DESCRIPTOR_H
#define ADD_FUNCTION_DESCRIPTOR_H

#include "FunctionDescriptor.h"

class AddFunctionDescriptor : public FunctionDescriptor {
public:
	AddFunctionDescriptor() : FunctionDescriptor("add", -1) {
	}

	virtual double Evaluate(const vector<unique_ptr<TreeItem>>& items) const override;
};

#endif // !ADD_FUNCTION_DESCRIPTOR_H