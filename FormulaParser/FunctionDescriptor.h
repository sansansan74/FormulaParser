#pragma once


#include "TreeItem.h"
#include "FunctionNames.h"
#include <string>
#include <vector>
#include <memory>

using namespace std;

class FunctionDescriptor {
public:

	const char* name;
	int paramCount;		// -1 - any > 0, else точное количество

	FunctionDescriptor(const char* name, int paramCount)
	{
		this->name = name;
		this->paramCount = paramCount;
	}

	string CheckParamCount(const string& name, int paramCount) const;


	virtual double Evaluate(const vector<unique_ptr<TreeItem>>& items) const = 0;
};
