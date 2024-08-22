#ifndef EXPRESSION_PARSER_H
#define EXPRESSION_PARSER_H

#include "Lexer.h"
#include "TreeOperation.h"
#include "TreeLeaf.h"
#include <memory>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <algorithm>

class ExpressionParser {
public:
    std::unique_ptr<TreeItem> Parse(const std::string& expression) {
        lexer_ = std::make_unique<Lexer>(expression);
        lexer_->NextToken();

        if (GetTokenType() == TokenType::End) {
            throw ParseFormulaException("Expression is empty.", 0);
        }

        auto tree = ParseExpression();

        if (GetTokenType() != TokenType::End) {
            throw ParseFormulaException("Unexpected token '" + GetTokenValue() + "' at position " + std::to_string(lexer_->GetIndex()), lexer_->GetIndex());
        }

        return tree;
    }

private:
    std::unique_ptr<Lexer> lexer_{};

    std::unique_ptr<TreeItem> ParseExpression() {
        std::vector<std::unique_ptr<TreeItem>> plusList;
        std::vector<std::unique_ptr<TreeItem>> minusList;

        auto unaryOperation = GetUnaryOperation();

        auto term = ParseMult();
        AddExpressionToList(plusList, minusList, unaryOperation, std::move(term));

        while (isAddOrMinisToken()) {
            auto operation = lexer_->GetToken();
            lexer_->NextToken();
            term = ParseMult();
            AddExpressionToList(plusList, minusList, operation, std::move(term));
        }

        if (!minusList.empty() && !plusList.empty()) {
            return std::make_unique<TreeOperation>("Subtract",
                std::make_unique<TreeOperation>("Add", std::move(plusList)),
                std::make_unique<TreeOperation>("Add", std::move(minusList)));
        }

        if (!plusList.empty()) {
            return CheckSumWithOneOperand(std::move(plusList));
        }

        return std::make_unique<TreeOperation>("Subtract", CreateZero(), CheckSumWithOneOperand(std::move(minusList)));
    }

    bool isAddOrMinisToken() const
    {
        return GetTokenType() == TokenType::Operation && (GetTokenValue() == "+" || GetTokenValue() == "-");
    }

    Token GetUnaryOperation() {
        if (GetTokenType() == TokenType::Operation &&
            (GetTokenValue() == "+" || GetTokenValue() == "-")) {
            auto operation = lexer_->GetToken();
            lexer_->NextToken();
            return operation;
        }
        return Token(TokenType::Operation, "+");
    }

    static void AddExpressionToList(std::vector<std::unique_ptr<TreeItem>>& plusList,
        std::vector<std::unique_ptr<TreeItem>>& minusList,
        const Token& operation,
        std::unique_ptr<TreeItem> treeItem) {
        if (operation.GetValue() == "+") {
            plusList.push_back(std::move(treeItem));
            return;
        }

        if (auto leaf = dynamic_cast<TreeLeaf*>(treeItem.get())) {
            plusList.push_back(std::make_unique<TreeLeaf>(-leaf->GetValue()));
            return;
        }

        minusList.push_back(std::move(treeItem));
    }

    static std::unique_ptr<TreeItem> CheckSumWithOneOperand(std::vector<std::unique_ptr<TreeItem>> items) {
        if (items.size() == 1) {
            return std::move(items[0]);
        }
        return std::make_unique<TreeOperation>("Add", std::move(items));
    }

    static std::unique_ptr<TreeItem> CheckMultWithOneOperand(std::vector<std::unique_ptr<TreeItem>> items) {
        if (items.size() == 1) {
            return std::move(items[0]);
        }
        return std::make_unique<TreeOperation>("Mult", std::move(items));
    }

    static std::unique_ptr<TreeItem> CheckOperationWithOneOperand(std::vector<std::unique_ptr<TreeItem>> items, const std::string& op) {
        if (items.size() == 1) {
            return std::move(items[0]);
        }
        return std::make_unique<TreeOperation>(op, std::move(items));
    }

    static std::unique_ptr<TreeLeaf> CreateZero() {
        return std::make_unique<TreeLeaf>(0);
    }

    std::unique_ptr<TreeItem> ParseMult() {
        std::vector<std::unique_ptr<TreeItem>> multItems;
        std::vector<std::unique_ptr<TreeItem>> divItems;

        auto tree = ParseFactor();
        multItems.push_back(std::move(tree));

        while (isMultOrDivToken()) {
            auto op = lexer_->GetToken();
            lexer_->NextToken();
            tree = ParseFactor();
            if (op.GetValue() == "*") {
                multItems.push_back(std::move(tree));
            }
            else {
                divItems.push_back(std::move(tree));
            }
        }

        if (!divItems.empty()) {
            return std::make_unique<TreeOperation>(
                "Divide",
                CheckMultWithOneOperand(std::move(multItems)),
                CheckMultWithOneOperand(std::move(divItems)));
        }

        return CheckMultWithOneOperand(std::move(multItems));
    }

    bool isMultOrDivToken() const
    {
        return GetTokenType() == TokenType::Operation && (GetTokenValue() == "*" || GetTokenValue() == "/");
    }

    TokenType GetTokenType() const {
        return lexer_->GetConstToken().GetType();
    }

    const std::string& GetTokenValue() const {
        return lexer_->GetConstToken().GetValue();
    }

    std::unique_ptr<TreeItem> ParseFactor() {
        // simple number 5 or 2.45
        if (GetTokenType() == TokenType::Numeric) {
            auto leaf = std::make_unique<TreeLeaf>(std::stod(GetTokenValue()));
            lexer_->NextToken();
            return leaf;
        }

        // ( expression )
        if (GetTokenType() == TokenType::Special && GetTokenValue() == "(") {
            lexer_->NextToken();
            auto expr = ParseExpression();
            if (GetTokenType() != TokenType::Special || GetTokenValue() != ")") {
                throw ParseFormulaException("Expected ')' at position " + std::to_string(lexer_->GetIndex()), lexer_->GetIndex());
            }
            lexer_->NextToken();
            return expr;
        }

        // parse function
        // function_without_args ()
        // function_with_args ( arg1, arg2, ... )
        if (GetTokenType() == TokenType::Identifier) {
            auto functionName = GetTokenValue();

            lexer_->NextToken();
            if (GetTokenType() != TokenType::Special || GetTokenValue() != "(") {
                throw ParseFormulaException("Expected '(' after function name at position " + std::to_string(lexer_->GetIndex()), lexer_->GetIndex());
            }
            lexer_->NextToken();
            auto function = std::make_unique<TreeOperation>(functionName);

            // read function params
            while (GetTokenType() != TokenType::Special || GetTokenValue() != ")") {
                auto arg = ParseExpression();
                function->GetItems().push_back(std::move(arg));
                if (GetTokenType() == TokenType::Special && GetTokenValue() == ",") {
                    lexer_->NextToken();
                    continue;
                }
            }

            if (GetTokenType() != TokenType::Special || GetTokenValue() != ")") {
                throw ParseFormulaException("Expected ')' at position " + std::to_string(lexer_->GetIndex()), lexer_->GetIndex());
            }

            CheckFunction(function);

            lexer_->NextToken();

            return function;
        }

        throw ParseFormulaException("Unexpected token '" + GetTokenValue() + "' at position " + std::to_string(lexer_->GetIndex()), lexer_->GetIndex());
    }

    void CheckFunction(const std::unique_ptr<TreeOperation>& treeOperation) {
        if (treeOperation->GetOperation() == "pi")
        {
            if (treeOperation->GetItems().size() != 0)
            {
                throw ParseFormulaException("Function PI must have no arguments at position " + std::to_string(lexer_->GetIndex()), lexer_->GetIndex());
            }
            return;
        }

        if (treeOperation->GetOperation() == "avg")
        {
            if (treeOperation->GetItems().size() == 0)
            {
                throw ParseFormulaException("Function AVG must have arguments at position " + std::to_string(lexer_->GetIndex()), lexer_->GetIndex());
            }
            return;
        }

        if (treeOperation->GetOperation() == "pow")
        {
            if (treeOperation->GetItems().size() != 2)
            {
                throw ParseFormulaException("Function POW must have 2 arguments at position " + std::to_string(lexer_->GetIndex()), lexer_->GetIndex());
            }
            return;
        }

        throw ParseFormulaException("Unknown function " + treeOperation->GetOperation() + " at position " + std::to_string(lexer_->GetIndex()), lexer_->GetIndex());
    }

};

#endif // EXPRESSION_PARSER_H
