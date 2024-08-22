#ifndef LEXER_H
#define LEXER_H

#include "Token.h"
#include "ParseFormulaException.h"
#include <string>
#include <cctype>
#include <stdexcept>
#include <sstream>

class Lexer {
public:
    explicit Lexer(const std::string& expression)
        : expression_(expression), index_(0) {}

    int GetIndex() const {
        return index_;
    }

    Token GetToken() const {
        return token_;
    }

    const Token& GetConstToken() const {
        return token_;
    }

    void NextToken() {
        SkipWhitespace();
        if (Eof()) {
            token_ = Token(TokenType::End, "");
            return;
        }

        char currentChar = CurrentChar();
        if (std::isdigit(currentChar) || currentChar == '.') {
            ParseNumber();
            return;
        }

        if (IsOperator(currentChar)) {
            ++index_;
            token_ = Token(TokenType::Operation, std::string(1, currentChar));
            return;
        }

        if (IsSpecial(currentChar)) {
            ++index_;
            token_ = Token(TokenType::Special, std::string(1, currentChar));
            return;
        }

        if (std::isalpha(currentChar)) {
            ParseIdentifier();
            return;
        }

        throw ParseFormulaException("Unexpected character '" + std::string(1, currentChar) + "' at position " + std::to_string(index_), index_);
    }

private:
    std::string expression_;
    int index_;
    Token token_;

    void ParseIdentifier() {
        std::ostringstream identifier;
        while (NotEof() && std::isalnum(CurrentChar())) {
            identifier << CurrentChar();
            ++index_;
        }
        token_ = Token(TokenType::Identifier, identifier.str());
    }

    void SkipWhitespace() {
        while (NotEof() && std::isspace(CurrentChar())) {
            ++index_;
        }
    }

    bool NotEof() const {
        return index_ < expression_.length();
    }

    bool Eof() const {
        return index_ >= expression_.length();
    }

    void ParseNumber() {
        std::ostringstream number;
        int dotCount = 0;
        while (NotEof() && (std::isdigit(CurrentChar()) || CurrentChar() == '.')) {
            if (CurrentChar() == '.') {
                if (dotCount > 0) {
                    throw std::runtime_error("Unexpected character '.' at position " + std::to_string(index_));
                }
                ++dotCount;
            }
            number << CurrentChar();
            ++index_;
        }
        token_ = Token(TokenType::Numeric, number.str());
    }

    char CurrentChar() const {
        return expression_[index_];
    }

    static bool IsOperator(char ch) {
        return ch == '+' || ch == '-' || ch == '*' || ch == '/';
    }

    static bool IsSpecial(char ch) {
        return ch == '(' || ch == ')' || ch == ',';
    }
};

#endif // LEXER_H
