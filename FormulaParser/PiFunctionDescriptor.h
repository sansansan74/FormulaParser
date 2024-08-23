#pragma once

#ifndef PIFUNCTIONDESCRIPTOR_H
#define PIFUNCTIONDESCRIPTOR_H

#include "FunctionDescriptor.h"

class PiFunctionDescriptor : public FunctionDescriptor {
public:
	PiFunctionDescriptor() : FunctionDescriptor(FUNCTION_PI, 0) {
	}

	virtual double Evaluate(const vector<unique_ptr<TreeItem>>& items) const override;
};

#endif

