#include "FactorialFunctionDescriptor.h"
#include "TreeLeaf.h"
#include "EvaluateFormulaException.h"

#include <cmath> 

int factorial(int n) {
	int result = 1;
	for (int i = 2; i <= n; i++)
	{
		result *= i;
	}

	return result;
}

double FactorialFunctionDescriptor::Evaluate(const vector<unique_ptr<TreeItem>>& items) const {
	auto argValue = UserFunctions::Evaluate(items[0]);
	auto roundedArgValue = std::round((float)argValue);
	if (roundedArgValue < 1)
	{
		throw EvaluateFormulaException("Factorial argument must be > 0. Argument=" + to_string(argValue));
	}
	return factorial(static_cast<int>(roundedArgValue));
}

