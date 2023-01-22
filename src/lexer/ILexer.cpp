//
// Created by redstone on 19.01.23.
//

#include "ILexer.h"

using namespace Lexing;

ILexer::ILexer(uint32_t line, uint32_t linePos) : line(line), linePos(linePos) {}

std::list<Token> ILexer::tokens() const {
    return list;
}

uint32_t ILexer::currentLine() const {
    return line;
}

uint32_t ILexer::currentLinePos() const {
    return linePos;
}
