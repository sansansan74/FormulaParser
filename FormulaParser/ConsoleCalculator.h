#ifndef CONSOLE_CALCULATOR_H
#define CONSOLE_CALCULATOR_H




#include <iostream>
#include "ExpressionParser.h"
#include "TreePrinter.h"
#include "TreeVisualizer.h"
#include "ExpressionEvaluator.h"
#include "FormulaParser.h"

static class ConsoleCalculator {
public:
	static void Calculate() {
		PrintInputPrompt();

		for (;;)
		{
			std::string expr = InputFormula();
			if (expr == "quit" || expr == "bye")
				return ;

			ProcessFormula(expr);
		}
	}
private:
	static void PrintResults(std::string& treeVisual, std::string& treeStr, const std::string& expr, double exprValue)
	{
		std::cout << "Expression tree:"
			<< std::endl << treeVisual
			<< std::endl << "Formula in functional style: " << treeStr
			<< std::endl << expr << "=" << exprValue
			<< std::endl << "--------------------------------------"
			<< std::endl;
	}

	static void PrintParsingError(const ParseFormulaException& ex, const std::string& expr)
	{
		std::string result(ex.GetPosition()-1, ' ');
		result += '^';

		std::cout << ex.what()
			<< std::endl << expr
			<< std::endl << result
			<< std::endl << "--------------------------------------"
			<< std::endl;
	}

	static void PrintEvaluationError(const std::domain_error& ex, const std::string& expr)
	{
		std::cout << ex.what()
			<< std::endl << "Execution error: "
			<< std::endl << expr
			<< std::endl << "--------------------------------------"
			<< std::endl;
	}

	static std::string InputFormula() {
		std::string formula;

		while (true) {
			std::cout << "Input formula or `quit` for quit: ";
			std::getline(std::cin, formula);

			// Удаляем начальные и конечные пробелы
			formula.erase(std::remove_if(formula.begin(), formula.end(), ::isspace), formula.end());

			if (!formula.empty()) {
				break;
			}

			std::cout << "Input line is empty. Try again." << std::endl;
		}
		return formula;
	}

	static void ProcessFormula(const std::string& expr)
	{
		ExpressionParser expressionParser;
		try
		{
			std::unique_ptr<TreeItem> tree = expressionParser.Parse(expr);
			std::string treeVisual = TreeVisualizer::Visualize(tree);
			std::string treeStr = TreePrinter::Print(tree);
			double exprValue = ExpressionEvaluator::Evaluate(tree);

			PrintResults(treeVisual, treeStr, expr, exprValue);
		}
		catch (const ParseFormulaException& ex)
		{
			PrintParsingError(ex, expr);
		}
		catch (const std::domain_error& dom) {
			PrintEvaluationError(dom, expr);
		}
	}


	static void PrintInputPrompt()
	{
		std::cout << "Formula syntax:"
			<< std::endl << "\tfloat numbers like -2, 6.3"
			<< std::endl << "\toperations +, -, *, /, (), pi(), avg(1,2,3), pow(2, 3)"
			<< std::endl
			<< std::endl << "Examples:"
			<< std::endl << "\t(2+3)*(5-3)/2"
			<< std::endl << "\t4/3*pi()*pow(5,3)"
			<< std::endl
			<< std::endl;
	}
};

#endif // CONSOLE_CALCULATOR_H