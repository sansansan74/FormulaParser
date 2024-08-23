#pragma once

#include "Lexer.h"
#include "TreeOperation.h"
#include "TreeLeaf.h"
#include "UserFunctions.h"

#include <memory>
#include <vector>

/*
The `ExpressionParser` class performs the parsing of an expression. 
The `Parse` method parses the expression and returns a tree representation of it. 
To achieve this, it uses the recursive descent method. If the expression contains 
syntax errors, the method will throw a `ParseFormulaException`.

Грамматика парсера в формулах Бэкуса-науэра:

expr ::= [+|-] sum | (expr)
sum ::= mult {+|- mult}
mult ::= item {*|/ item}
item ::= double | func
double ::= intNumber | doubleNumber
func ::= funcName ( expr_list )
expr_list ::= | expr {, expr}
funcName ::= avg | pow | pi
Где:
[] - означает, что содержиемое есть, или нет
{} - содержимое может повторяться 0 или более раз
*/

using namespace std;

class ExpressionParser {
public:
    unique_ptr<TreeItem> Parse(const string& expression);

private:
    unique_ptr<Lexer> lexer_{};

    unique_ptr<TreeItem> ParseExpression();

    bool isAddOrMinisToken() const
    {
        return GetTokenType() == TokenType::Operation && (GetTokenValue() == "+" || GetTokenValue() == "-");
    }

    Token GetUnaryOperation();

    static void AddExpressionToList(vector<unique_ptr<TreeItem>>& plusList,
        vector<unique_ptr<TreeItem>>& minusList,
        const Token& operation,
        unique_ptr<TreeItem> treeItem);

    static unique_ptr<TreeItem> CheckSumWithOneOperand(vector<unique_ptr<TreeItem>> items) {
        if (items.size() == 1) {
            return move(items[0]);
        }
        return make_unique<TreeOperation>(FUNCTION_ADD, move(items));
    }

    static unique_ptr<TreeItem> CheckMultWithOneOperand(vector<unique_ptr<TreeItem>> items) {
        if (items.size() == 1) {
            return move(items[0]);
        }
        return make_unique<TreeOperation>(FUNCTION_MULT, move(items));
    }

    static unique_ptr<TreeItem> CheckOperationWithOneOperand(vector<unique_ptr<TreeItem>> items, const string& op) {
        if (items.size() == 1) {
            return move(items[0]);
        }
        return make_unique<TreeOperation>(op, move(items));
    }

    static unique_ptr<TreeLeaf> CreateZero() {
        return make_unique<TreeLeaf>(0);
    }

    unique_ptr<TreeItem> ParseMult();

    bool isMultOrDivToken() const
    {
        return GetTokenType() == TokenType::Operation && (GetTokenValue() == "*" || GetTokenValue() == "/");
    }

    TokenType GetTokenType() const {
        return lexer_->GetConstToken().GetType();
    }

    const string& GetTokenValue() const {
        return lexer_->GetConstToken().GetValue();
    }

    unique_ptr<TreeItem> ParseFactor();

    void CheckFunctionName(const std::string& functionName) {
        if (!UserFunctions::isContainsFunctionByName(functionName))
            CreateParseFormulaException("Unexpected funcions '" + functionName + "'");
    }
    

    void CheckFunctionParamNumbers(const unique_ptr<TreeOperation>& treeOperation) {
        auto errorMessage = UserFunctions::CheckParamsCount(treeOperation->GetOperation(), treeOperation->GetItems().size());
        if (!errorMessage.empty())
        {
            CreateParseFormulaException("Function " + treeOperation->GetOperation() + " " + errorMessage);
        }
    }

    void CreateParseFormulaException(const string& message) const {
        lexer_->CreateParseFormulaException(message);
    }

};