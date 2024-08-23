
#pragma once

#ifndef MULT_FUNCTION_DESCRIPTOR_H
#define MULT_FUNCTION_DESCRIPTOR_H

#include "FunctionDescriptor.h"

class MultFunctionDescriptor : public FunctionDescriptor {
public:
	MultFunctionDescriptor() : FunctionDescriptor("mult", -1) {
	}

	virtual double Evaluate(const vector<unique_ptr<TreeItem>>& items) const override;
};

#endif // !MULT_FUNCTION_DESCRIPTOR_H