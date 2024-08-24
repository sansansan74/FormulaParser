#pragma once

#include "Token.h"
#include "ParseFormulaException.h"
#include <string>
#include <cctype>
#include <stdexcept>
#include <sstream>

using namespace std;

/*
The Lexer class converts a set of characters into tokens.
GetToken() method returns the next token. 
If the input string contains errors, the method throws an exception 
with a description of the error and its position in the string.
*/

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
        return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '!';
    }

    static bool IsSpecial(char ch) {
        return ch == '(' || ch == ')' || ch == ',' ;
    }
};

