#include "Token.h"

#include <utility>

using namespace Lexing;

Token::Token(uint32_t line, uint32_t linePos, TokenType type, std::string value)
    : tokenType(type), tokenValue(std::move(value)), tokenLine(line), tokenLinePos(linePos) {}

TokenType Token::type() const {
    return tokenType;
}

std::string Token::value() const {
    return tokenValue;
}

uint32_t Token::line() const {
    return tokenLine;
}

uint32_t Token::linePos() const {
    return tokenLinePos;
}
