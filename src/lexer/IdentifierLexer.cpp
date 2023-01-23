#include "IdentifierLexer.h"

using namespace Lexing;

IdentifierLexer::IdentifierLexer(uint32_t& line, uint32_t& linePos, std::list<Token>& tokens) : Lexer(line, linePos, tokens) {}

void IdentifierLexer::tokenize(std::istream& input) {
}
