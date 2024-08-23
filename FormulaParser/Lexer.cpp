#include "Lexer.h"

void Lexer::NextToken() {
    SkipWhitespace();
    if (Eof()) {
        token_ = Token(TokenType::End, "");
        return;
    }

    char currentChar = CurrentChar();
    if (isdigit(currentChar) || currentChar == '.') {
        ParseNumber();
        return;
    }

    if (IsOperator(currentChar)) {
        ++index_;
        token_ = Token(TokenType::Operation, string(1, currentChar));
        return;
    }

    if (IsSpecial(currentChar)) {
        ++index_;
        token_ = Token(TokenType::Special, string(1, currentChar));
        return;
    }

    if (isalpha(currentChar)) {
        ParseIdentifier();
        return;
    }

    CreateParseFormulaException("Unexpected character '" + string(1, currentChar) + "'");
}

void Lexer::ParseIdentifier() {
    ostringstream identifier;
    while (NotEof() && isalnum(CurrentChar())) {
        identifier << CurrentChar();
        ++index_;
    }
    token_ = Token(TokenType::Identifier, identifier.str());
}

void Lexer::SkipWhitespace() {
    while (NotEof() && isspace(CurrentChar())) {
        ++index_;
    }
}

void Lexer::ParseNumber() {
    ostringstream number;
    int dotCount = 0;

    while (NotEof() && (isdigit(CurrentChar()) || CurrentChar() == '.')) {
        if (CurrentChar() == '.') {
            if (dotCount > 0) {
                CreateParseFormulaException("Unexpected character '.'");
            }
            ++dotCount;
        }
        number << CurrentChar();
        ++index_;
    }

    token_ = Token(TokenType::Numeric, number.str());
}
