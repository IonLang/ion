//
// Created by redstone on 19.01.23.
//

#include "Lexer.h"

using namespace Lexing;

Lexer::Lexer(uint32_t& line, uint32_t& linePos) : line(line), linePos(linePos) {}

std::list<Token> Lexer::tokens() const {
    return list;
}

uint32_t Lexer::currentLine() const {
    return line;
}

uint32_t Lexer::currentLinePos() const {
    return linePos;
}
