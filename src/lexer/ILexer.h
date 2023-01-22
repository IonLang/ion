#pragma once

#include <istream>
#include <list>
#include "lexer/token/Token.h"

namespace Lexing {

class ILexer {
public:
    ILexer(uint32_t line, uint32_t linePos);
    virtual ~ILexer() {};

    virtual void tokenize(std::istream& input) = 0;

    std::list<Token> tokens() const;
    uint32_t currentLine() const;
    uint32_t currentLinePos() const;
protected:
    std::list<Token> list;
    uint32_t line = 0;
    uint32_t linePos = 0;
};

}  // namespace Lexing
