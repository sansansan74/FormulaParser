#ifndef TOKEN_H
#define TOKEN_H

#include "TokenType.h"
#include <string>

class Token {
public:
    Token()
    {}

    Token(TokenType type, const std::string& value)
        : type_(type), value_(value) {}

    TokenType GetType() const {
        return type_;
    }

    const std::string& GetValue() const {
        return value_;
    }

    std::string ToString() const {
        return "(" + TokenTypeToString(type_) + ", " + value_ + ")";
    }

private:
    TokenType type_;
    std::string value_;

    std::string TokenTypeToString(TokenType type) const {
        switch (type) {
        case TokenType::Operation: return "Operation";
        case TokenType::Identifier: return "Identifier";
        case TokenType::Special: return "Special";
        case TokenType::Numeric: return "Numeric";
        case TokenType::End: return "End";
        default: return "Unknown";
        }
    }
};

#endif // TOKEN_H
