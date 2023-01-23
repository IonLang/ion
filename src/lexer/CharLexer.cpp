#include "CharLexer.h"

using namespace Lexing;

CharLexer::CharLexer(uint32_t& line, uint32_t& linePos, std::list<Token>& tokens) : Lexer(line, linePos, tokens) {}

void CharLexer::tokenize(std::istream& input) {
}
