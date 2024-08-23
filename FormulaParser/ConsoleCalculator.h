#pragma once

#include <string>
#include "EvaluateFormulaException.h"
#include "ParseFormulaException.h"

using namespace std;

class ConsoleCalculator {
public:
	static void Calculate();
private:
	static void PrintResults(string& treeVisual, string& treeStr, const string& expr, double exprValue);

	static void PrintParsingError(const ParseFormulaException& ex, const string& expr);

	static void PrintEvaluationError(const EvaluateFormulaException& ex, const string& expr);

	static string InputFormula();

	static void ProcessFormula(const string& expr);


	static void PrintInputPrompt();
};
