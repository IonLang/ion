#pragma once

#include <istream>
#include <list>
#include "lexer/token/Token.h"

namespace Lexing {

class Lexer {
public:
    Lexer(uint32_t& line, uint32_t& linePos, std::list<Token>& tokens);
    virtual ~Lexer() {};

    virtual void tokenize(std::istream& input) = 0;

    uint32_t currentLine() const;
    uint32_t currentLinePos() const;
protected:
    uint32_t& line;
    uint32_t& linePos;
    std::list<Token>& tokens;
};

}  // namespace Lexing
