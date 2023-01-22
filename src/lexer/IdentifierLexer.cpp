#include "IdentifierLexer.h"

using namespace Lexing;

IdentifierLexer::IdentifierLexer(uint32_t& line, uint32_t& linePos) : Lexer(line, linePos) {}

std::list<Token> IdentifierLexer::tokenize(std::istream& input) {
    return std::list<Token>();
}
