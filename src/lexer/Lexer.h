#pragma once

#include <istream>
#include <list>
#include "lexer/token/Token.h"

namespace Lexing {

class Lexer {
public:
    Lexer(uint32_t& line, uint32_t& linePos);
    virtual ~Lexer() {};

    virtual void tokenize(std::istream& input) = 0;

    std::list<Token> tokens() const;
    uint32_t currentLine() const;
    uint32_t currentLinePos() const;
protected:
    std::list<Token> list;
    uint32_t& line;
    uint32_t& linePos;
};

}  // namespace Lexing
