//
// Created by redstone on 19.01.23.
//

#include "Lexer.h"

using namespace Lexing;

Lexer::Lexer(uint32_t& line, uint32_t& linePos, std::list<Token>& tokens) : line(line), linePos(linePos), tokens(tokens) {}
