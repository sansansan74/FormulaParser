#include "Token.h"

std::string Token::TokenTypeToString(TokenType type) const {
    switch (type) {
    case TokenType::Operation: return "Operation";
    case TokenType::Identifier: return "Identifier";
    case TokenType::Special: return "Special";
    case TokenType::Numeric: return "Numeric";
    case TokenType::End: return "End";
    default: return "Unknown";
    }
}
