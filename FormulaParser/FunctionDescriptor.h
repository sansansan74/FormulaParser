#pragma once

/*
	Describe one user function
*/

#include "TreeItem.h"
#include "FunctionNames.h"
#include <string>
#include <vector>
#include <memory>

using namespace std;

/// <summary>
/// Describe one user function
/// </summary>
class FunctionDescriptor {
public:

	const char* functionName;
	int paramCount;		// -1 - any > 0, else точное количество

	FunctionDescriptor(const char* functionName, int paramCount)
	{
		this->functionName = functionName;
		this->paramCount = paramCount;
	}

	string CheckParamCount(const string& functionName, int paramCount) const;


	virtual double Evaluate(const vector<unique_ptr<TreeItem>>& items) const = 0;
};
