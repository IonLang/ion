#include "IdentifierLexer.h"

using namespace Lexing;
using namespace FileAccess;

IdentifierLexer::IdentifierLexer(std::list<Token>& tokens) : Lexer(tokens) {}

void IdentifierLexer::tokenize(FileReader& input) {
    std::string buffer = "";
    char c;
    while (input.good()) {
        c = input.getch();
        switch (c) {
            case '\n':
                throw std::exception();
            case '`':
                tokens.push_back(Token(input.getLine(), input.getLinePos() - buffer.length(), TokenType::identifier, buffer));
                tokens.push_back(Token(input.getLine(), input.getLinePos() - 1, TokenType::grave));
                return;
            default:
                buffer += c;
                break;
        }
    }
}
