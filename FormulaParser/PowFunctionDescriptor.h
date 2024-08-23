#pragma once

#ifndef POWFUNCTIONDESCRIPTOR_H
#define POW_FUNCTION_DESCRIPTOR_H

#include "FunctionDescriptor.h"
#include "UserFunctions.h"

class PowFunctionDescriptor : public FunctionDescriptor {
public:
	PowFunctionDescriptor() : FunctionDescriptor("pow", 2) {
	}

	virtual double Evaluate(const vector<unique_ptr<TreeItem>>& items) const override;
};

#endif // !POWFUNCTIONDESCRIPTOR_H


