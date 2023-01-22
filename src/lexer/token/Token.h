#pragma once

#include <string>
#include "TokenType.h"
namespace Lexing {

class Token {
public:
    Token(uint32_t line, uint32_t linePos, TokenType type, std::string value = "");

    TokenType type() const;
    std::string value() const;
    uint32_t line() const;
    uint32_t linePos() const;
private:
    TokenType tokenType;
    std::string tokenValue;
    uint32_t tokenLine;
    uint32_t tokenLinePos;
};

}
