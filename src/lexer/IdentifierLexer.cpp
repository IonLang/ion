#include "IdentifierLexer.h"

using namespace Lexing;

IdentifierLexer::IdentifierLexer(uint32_t& line, uint32_t& linePos) : Lexer(line, linePos) {}

void IdentifierLexer::tokenize(std::istream& input) {
}
