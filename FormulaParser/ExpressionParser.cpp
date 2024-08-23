#include "ExpressionParser.h"

unique_ptr<TreeItem> ExpressionParser::Parse(const string& expression) {
    lexer_ = make_unique<Lexer>(expression);
    lexer_->NextToken();

    if (GetTokenType() == TokenType::End) {
        throw ParseFormulaException("Expression is empty.", 0);
    }

    auto tree = ParseExpression();

    if (GetTokenType() != TokenType::End) {
        CreateParseFormulaException("Unexpected token '" + GetTokenValue() + "'");
    }

    return tree;
}

unique_ptr<TreeItem> ExpressionParser::ParseExpression() {
    vector<unique_ptr<TreeItem>> plusList;
    vector<unique_ptr<TreeItem>> minusList;

    auto unaryOperation = GetUnaryOperation();

    auto term = ParseMult();
    AddExpressionToList(plusList, minusList, unaryOperation, move(term));

    while (isAddOrMinisToken()) {
        auto operation = lexer_->GetToken();
        lexer_->NextToken();
        term = ParseMult();
        AddExpressionToList(plusList, minusList, operation, move(term));
    }

    if (!minusList.empty() && !plusList.empty()) {
        return make_unique<TreeOperation>("subtract",
            make_unique<TreeOperation>("add", move(plusList)),
            make_unique<TreeOperation>("add", move(minusList)));
    }

    if (!plusList.empty()) {
        return CheckSumWithOneOperand(move(plusList));
    }

    return make_unique<TreeOperation>("subtract", CreateZero(), CheckSumWithOneOperand(move(minusList)));
}

Token ExpressionParser::GetUnaryOperation() {
    if (GetTokenType() == TokenType::Operation &&
        (GetTokenValue() == "+" || GetTokenValue() == "-")) {
        auto operation = lexer_->GetToken();
        lexer_->NextToken();
        return operation;
    }
    return Token(TokenType::Operation, "+");
}

void ExpressionParser::AddExpressionToList(vector<unique_ptr<TreeItem>>& plusList, vector<unique_ptr<TreeItem>>& minusList, const Token& operation, unique_ptr<TreeItem> treeItem) {
    if (operation.GetValue() == "+") {
        plusList.push_back(move(treeItem));
        return;
    }

    if (auto leaf = dynamic_cast<TreeLeaf*>(treeItem.get())) {
        plusList.push_back(make_unique<TreeLeaf>(-leaf->GetValue()));
        return;
    }

    minusList.push_back(move(treeItem));
}

unique_ptr<TreeItem> ExpressionParser::ParseMult() {
    vector<unique_ptr<TreeItem>> multItems;
    vector<unique_ptr<TreeItem>> divItems;

    auto tree = ParseFactor();
    multItems.push_back(move(tree));

    while (isMultOrDivToken()) {
        auto op = lexer_->GetToken();
        lexer_->NextToken();
        tree = ParseFactor();
        if (op.GetValue() == "*") {
            multItems.push_back(move(tree));
        }
        else {
            divItems.push_back(move(tree));
        }
    }

    if (!divItems.empty()) {
        return make_unique<TreeOperation>(
            "divide",
            CheckMultWithOneOperand(move(multItems)),
            CheckMultWithOneOperand(move(divItems)));
    }

    return CheckMultWithOneOperand(move(multItems));
}

unique_ptr<TreeItem> ExpressionParser::ParseFactor() {
    // simple number 5 or 2.45
    if (GetTokenType() == TokenType::Numeric) {
        auto leaf = make_unique<TreeLeaf>(stod(GetTokenValue()));
        lexer_->NextToken();
        return leaf;
    }

    // ( expression )
    if (GetTokenType() == TokenType::Special && GetTokenValue() == "(") {
        lexer_->NextToken();
        auto expr = ParseExpression();
        if (GetTokenType() != TokenType::Special || GetTokenValue() != ")") {
            CreateParseFormulaException("Expected ')'");
        }
        lexer_->NextToken();
        return expr;
    }

    // parse function
    // function_without_args ()
    // function_with_args ( arg1, arg2, ... )
    if (GetTokenType() == TokenType::Identifier) {
        auto functionName = GetTokenValue();
        CheckFunctionName(functionName);

        lexer_->NextToken();
        if (GetTokenType() != TokenType::Special || GetTokenValue() != "(") {
            CreateParseFormulaException("Expected '(' after function name " + functionName);
        }
        lexer_->NextToken();
        auto function = make_unique<TreeOperation>(functionName);

        // read function params
        while (GetTokenType() != TokenType::Special || GetTokenValue() != ")") {
            auto arg = ParseExpression();
            function->GetItems().push_back(move(arg));
            if (GetTokenType() == TokenType::Special && GetTokenValue() == ",") {
                lexer_->NextToken();
                continue;
            }
        }

        if (GetTokenType() != TokenType::Special || GetTokenValue() != ")") {
            CreateParseFormulaException("Expected ')'");
        }

        CheckFunctionParamNumbers(function);

        lexer_->NextToken();

        return function;
    }

    CreateParseFormulaException("Unexpected token '" + GetTokenValue() + "'");
}
