#include "StringLexer.h"

using namespace Lexing;

StringLexer::StringLexer(uint32_t& line, uint32_t& linePos, std::list<Token>& tokens) : Lexer(line, linePos, tokens) {}

void StringLexer::tokenize(std::istream& input) {
    char c;
    while (input.good()) {
        input.get(c);
        switch (c) {
            case '"':
                tokens.push_back(Token(line, linePos, TokenType::doubleQuote));
                return;
            case '\\':
                break;
            case '$':
                break;
            default:
                buffer += c;
                break;
        }
    }
}
