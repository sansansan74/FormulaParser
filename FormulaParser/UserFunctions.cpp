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
vector<const FunctionDescriptor*> UserFunctions::desc = {
	new PiFunctionDescriptor(),
	new AvgFunctionDescriptor(),
	new PowFunctionDescriptor(),
	new AddFunctionDescriptor(),
	new SubtractFunctionDescriptor(),
	new MultFunctionDescriptor(),
	new DivideFunctionDescriptor()
};

bool UserFunctions::ContainFunctions(const string& name) {
	auto it = find_if(begin(desc), end(desc),
		[name](const FunctionDescriptor* func) {
			return name == func->name;
		});

	// Возвращаем true, если элемент найден, иначе false
	return it != end(desc);
}

string UserFunctions::CheckParamNumbers(const string& name, int paramCount) {
	// todo change to map
	for (const auto f : desc)
	{
		if (f->name == name) {
			return f->CheckParamCount(name, paramCount);
		}
	}

	return "";
}

double UserFunctions::Evaluate(const string& name, const vector<unique_ptr<TreeItem>>& items) {
	for (const auto f : desc)
	{
		if (f->name == name) {
			return f->Evaluate(items);
		}
	}

	// todo Exceptions change to ParseException & EvaluateExceptions
	throw EvaluateFormulaException("Нет такой функции");
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
