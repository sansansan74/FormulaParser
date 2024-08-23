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
map<string, const FunctionDescriptor*> UserFunctions::functionDescriptors = {
	// standart 4 functions: + - * /
	{ string(FUNCTION_ADD), new AddFunctionDescriptor() },
	{ string(FUNCTION_SUBTRACT), new SubtractFunctionDescriptor() },
	{ string(FUNCTION_MULT), new MultFunctionDescriptor() },
	{ string(FUNCTION_DIVIDE), new DivideFunctionDescriptor() },

	// user functions
	{ string(FUNCTION_PI), new PiFunctionDescriptor() },
	{ string(FUNCTION_AVG), new AvgFunctionDescriptor() },
	{ string(FUNCTION_POW), new PowFunctionDescriptor() },

};

bool UserFunctions::isContainsFunctionByName(const string& functionName) {
	try {
		auto functionDescriptor = functionDescriptors.at(functionName);
		return true;
	}
	catch (const std::out_of_range& e) {
		false;
	}
}

/// <summary>
/// Check number params in functions
/// </summary>
/// <param name="functionName">name of function</param>
/// <param name="paramCount">fact param count</param>
/// <returns>error message, if error occure</returns>
string UserFunctions::CheckParamsCount(const string& functionName, int paramCount) {
	try {
		auto functionDescriptor = functionDescriptors.at(functionName);
		return functionDescriptor->CheckParamCount(functionName, paramCount);
	}
	catch (const std::out_of_range& e) {
		throw EvaluateFormulaException("No such function " + functionName);
	}

	return "";
}

double UserFunctions::EvaluateTreeItemValue(const string& functionName, const vector<unique_ptr<TreeItem>>& params) {
	try {
		auto functionDescriptor = functionDescriptors.at(functionName);
		return functionDescriptor->Evaluate(params);
	}
	catch (const std::out_of_range& e) {
		throw EvaluateFormulaException("No such function " + functionName);
	}
}

double UserFunctions::Evaluate(const unique_ptr<TreeItem>& treeItem) {
	if (const TreeLeaf* leaf = dynamic_cast<const TreeLeaf*>(treeItem.get())) {
		return leaf->GetValue();
	}

	if (TreeOperation* operation = dynamic_cast<TreeOperation*>(treeItem.get())) {
		return EvaluateTreeItemValue(operation->GetOperation(), operation->GetItems());
	}

	throw EvaluateFormulaException("Unknown TreeItem type");
}
