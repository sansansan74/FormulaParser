#pragma once


#include "FunctionDescriptor.h"

class PiFunctionDescriptor : public FunctionDescriptor {
public:
	PiFunctionDescriptor() : FunctionDescriptor(FUNCTION_PI, 0) {
	}

	virtual double Evaluate(const vector<unique_ptr<TreeItem>>& items) const override;
};


