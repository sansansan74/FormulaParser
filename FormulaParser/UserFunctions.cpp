#include "AddFunctionDescriptor.h"
#include "AvgFunctionDescriptor.h"
#include "DivideFunctionDescriptor.h"
#include "EvaluateFormulaException.h"
#include "MultFunctionDescriptor.h"
#include "PiFunctionDescriptor.h"
#include "PowFunctionDescriptor.h"
#include "SubtractFunctionDescriptor.h"
#include "TreeLeaf.h"
#include "TreeOperation.h"
#include "UserFunctions.h"

#include <memory>
#include <string>


// Инициализация статического массива
map<string, const FunctionDescriptor*> UserFunctions::desc = {
	{ string(FUNCTION_PI), new PiFunctionDescriptor() },
	{ string(FUNCTION_AVG), new AvgFunctionDescriptor() },
	{ string(FUNCTION_POW), new PowFunctionDescriptor() },
	{ string(FUNCTION_ADD), new AddFunctionDescriptor() },
	{ string(FUNCTION_SUBTRACT), new SubtractFunctionDescriptor() },
	{ string(FUNCTION_MULT), new MultFunctionDescriptor() },
	{ string(FUNCTION_DIVIDE), new DivideFunctionDescriptor() }
};

bool UserFunctions::ContainFunctions(const string& name) {
	try {
		auto functionDescriptor = desc.at(name);
		return true;
	}
	catch (const std::out_of_range& e) {
		false;
	}
}

string UserFunctions::CheckParamNumbers(const string& name, int paramCount) {
	try {
		auto functionDescriptor = desc.at(name);
		return functionDescriptor->CheckParamCount(name, paramCount);
	}
	catch (const std::out_of_range& e) {
		throw EvaluateFormulaException("No such function " + name);
	}

	return "";
}

double UserFunctions::Evaluate(const string& name, const vector<unique_ptr<TreeItem>>& items) {
	try {
		auto functionDescriptor = desc.at(name);
		return functionDescriptor->Evaluate(items);
	}
	catch (const std::out_of_range& e) {
		throw EvaluateFormulaException("No such function " + name);
	}
}

double UserFunctions::Evaluate(const unique_ptr<TreeItem>& item) {
	if (const TreeLeaf* leaf = dynamic_cast<const TreeLeaf*>(item.get())) {
		return leaf->GetValue();
	}

	if (TreeOperation* operation = dynamic_cast<TreeOperation*>(item.get())) {
		return Evaluate(operation->GetOperation(), operation->GetItems());
	}
	throw EvaluateFormulaException("Unknown TreeItem type");
}
