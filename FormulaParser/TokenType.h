#pragma once

/*
The enumeration contains the types of tokens that are returned by the `Lexer` parser.
*/

enum class TokenType {
    Operation,
    Identifier,
    Special,
    Numeric,
    End
};

