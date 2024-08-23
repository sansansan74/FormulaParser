#ifndef LEXER_H
#define LEXER_H

#include "Token.h"
#include "ParseFormulaException.h"
#include <string>
#include <cctype>
#include <stdexcept>
#include <sstream>

using namespace std;

class Lexer {
public:
    explicit Lexer(const string& expression)
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

    void NextToken();

    void CreateParseFormulaException(const string& message) const {
        throw ParseFormulaException(message + " at position " + to_string(index_), index_);
    }

private:
    string expression_;
    int index_;
    Token token_;

    void ParseIdentifier();

    void SkipWhitespace();

    bool NotEof() const {
        return index_ < expression_.length();
    }

    bool Eof() const {
        return index_ >= expression_.length();
    }

    void ParseNumber();

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
