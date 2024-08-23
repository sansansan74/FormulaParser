#include "ConsoleCalculator.h"
#include "ExpressionParser.h"
#include "TreePrinter.h"
#include "TreeVisualizer.h"
#include <iostream>

using namespace std;

void ConsoleCalculator::Calculate() {
	PrintInputPrompt();

	for (;;)
	{
		string expr = InputFormula();
		if (expr == "quit" || expr == "bye")
			return;

		ProcessFormula(expr);
	}
}

void ConsoleCalculator::PrintResults(string& treeVisual, string& treeStr, const string& expr, double exprValue)
{
	cout << "Expression tree:"
		<< endl << treeVisual
		<< endl << "Formula in functional style: " << treeStr
		<< endl << expr << "=" << exprValue
		<< endl << "--------------------------------------"
		<< endl;
}

void ConsoleCalculator::PrintParsingError(const ParseFormulaException& ex, const string& expr)
{
	string result(ex.GetPosition() - 1, ' ');
	result += '^';

	cout << ex.what()
		<< endl << expr
		<< endl << result
		<< endl << "--------------------------------------"
		<< endl;
}

void ConsoleCalculator::PrintEvaluationError(const EvaluateFormulaException& ex, const string& expr)
{
	cout << ex.what()
		<< endl << "Execution error: "
		<< endl << expr
		<< endl << "--------------------------------------"
		<< endl;
}

string ConsoleCalculator::InputFormula() {
	string formula;

	while (true) {
		cout << "Input formula or `quit` for quit: ";
		getline(cin, formula);

		// Удаляем начальные и конечные пробелы
		formula.erase(remove_if(formula.begin(), formula.end(), ::isspace), formula.end());

		if (!formula.empty()) {
			break;
		}

		cout << "Input line is empty. Try again." << endl;
	}
	return formula;
}

void ConsoleCalculator::ProcessFormula(const string& expr)
{
	ExpressionParser expressionParser;
	try
	{
		unique_ptr<TreeItem> tree = expressionParser.Parse(expr);
		string treeVisual = TreeVisualizer::Visualize(tree);
		string treeStr = TreePrinter::Print(tree);
		double exprValue = UserFunctions::Evaluate(tree);

		PrintResults(treeVisual, treeStr, expr, exprValue);
	}
	catch (const ParseFormulaException& ex)
	{
		PrintParsingError(ex, expr);
	}
	catch (const EvaluateFormulaException& ex) {
		PrintEvaluationError(ex, expr);
	}
}

void ConsoleCalculator::PrintInputPrompt()
{
	cout << "Formula syntax:"
		<< endl << "\tfloat numbers like -2, 6.3"
		<< endl << "\toperations +, -, *, /, (), pi(), avg(1,2,3), pow(2, 3)"
		<< endl
		<< endl << "Examples:"
		<< endl << "\t(2+3)*(5-3)/2"
		<< endl << "\t4/3*pi()*pow(5,3)"
		<< endl
		<< endl;
}
