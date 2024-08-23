#pragma once

#ifndef AVGFUNCTIONDESCRIPTOR_H
#define AVGFUNCTIONDESCRIPTOR_H

#include "FunctionDescriptor.h"

class AvgFunctionDescriptor : public FunctionDescriptor {
public:
	AvgFunctionDescriptor() : FunctionDescriptor("avg", -1) {
	}

	 virtual double Evaluate(const vector<unique_ptr<TreeItem>>& items) const override;
};

#endif // !AVGFUNCTIONDESCRIPTOR_H



