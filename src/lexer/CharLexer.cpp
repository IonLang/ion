#include "CharLexer.h"

using namespace Lexing;

CharLexer::CharLexer(uint32_t& line, uint32_t& linePos) : Lexer(line, linePos) {}

void CharLexer::tokenize(std::istream& input) {
}
