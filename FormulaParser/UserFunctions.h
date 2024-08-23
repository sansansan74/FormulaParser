#pragma once

/*
Contains descriptions of user-defined functions. To add a custom function, it needs to be registered in `FunctionDescriptor.cpp`.
*/

#include "TreeItem.h"
#include "FunctionDescriptor.h"

#include <string>
#include <map>

using namespace std;

/// <summary>
/// Contains descriptions of user-defined functions. To add a custom function, it needs to be registered in `FunctionDescriptor.cpp`.
/// </summary>
class UserFunctions {
	static map<string, const FunctionDescriptor*> functionDescriptors;
public:
	static bool isContainsFunctionByName(const string& functionName);

	static string CheckParamsCount(const string& functionName, int paramCount);

	static double Evaluate(const unique_ptr<TreeItem>& item);
private:
	static double EvaluateTreeItemValue(const string& functionName, const vector<unique_ptr<TreeItem>>& params);
};



