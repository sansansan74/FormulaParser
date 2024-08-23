#pragma once
#ifndef USERFUNCTIONS_H
#define USERFUNCTIONS_H

#include "TreeItem.h"
#include "FunctionDescriptor.h"

#include <string>
#include <vector>

using namespace std;

class UserFunctions {
	static vector<const FunctionDescriptor*> desc;
public:
	static bool ContainFunctions(const string& name);

	static string CheckParamNumbers(const string& name, int paramCount);

	static double Evaluate(const string& name, const vector<unique_ptr<TreeItem>>&  items);

	static double Evaluate(const unique_ptr<TreeItem>& item);
	
};

#endif // !USERFUNCTIONS_H


