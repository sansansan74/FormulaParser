#pragma once

/*
Contains descriptions of user-defined functions. To add a custom function, it needs to be registered in `FunctionDescriptor.cpp`.
*/

#include "TreeItem.h"
#include "FunctionDescriptor.h"

#include <string>
#include <map>

using namespace std;

class UserFunctions {
	static map<string, const FunctionDescriptor*> desc;
public:
	static bool ContainFunctions(const string& name);

	static string CheckParamNumbers(const string& name, int paramCount);

	static double Evaluate(const unique_ptr<TreeItem>& item);
private:
	static double EvaluateTreeItemValue(const string& name, const vector<unique_ptr<TreeItem>>& items);	
};



