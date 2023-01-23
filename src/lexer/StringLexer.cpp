#include "StringLexer.h"

using namespace Lexing;

StringLexer::StringLexer(uint32_t& line, uint32_t& linePos, std::list<Token>& tokens) : Lexer(line, linePos, tokens) {}

void StringLexer::tokenize(std::istream& input) {
}
