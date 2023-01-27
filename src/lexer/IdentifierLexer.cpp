#include "IdentifierLexer.h"

using namespace Lexing;

IdentifierLexer::IdentifierLexer(uint32_t& line, uint32_t& linePos, std::list<Token>& tokens) : Lexer(line, linePos, tokens) {}

void IdentifierLexer::tokenize(std::istream& input) {
    std::string buffer = "";
    char c;
    while (input.good()) {
        input.get(c);
        switch (c) {
            case '\n':
                throw std::exception();
            case '`':
                tokens.push_back(Token(line, linePos - buffer.length(), TokenType::identifier, buffer));
                tokens.push_back(Token(line, linePos - 1, TokenType::grave));
                return;
            default:
                buffer += c;
                break;
        }
    }
}
