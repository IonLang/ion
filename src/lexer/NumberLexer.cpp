#include "NumberLexer.h"
#include <iostream>

using namespace Lexing;
using namespace FileAccess;

NumberLexer::NumberLexer(std::list<Token>& tokens) : Lexer(tokens) {}

void NumberLexer::tokenize(FileReader& input) {
    while (true) {
        char c = input.getch();
        if (c == '_') {
            continue;
        } else if ((c == 'x' || c == 'b') && buffer.back() == '0' && buffer.size() == 1) {
            buffer += c;
            tokens.push_back(Token(input.getLine(), input.getLinePos() - 2, c == 'x' ? TokenType::hexLiteralMarker : TokenType::binLiteralMarker));
            buffer = "";
            continue;
        } else if (isxdigit(c)) {
            buffer += c;
        } else {
            processToken(input);
            input.putch(c);
            return;
        }
    }
}

void NumberLexer::processToken(FileReader& input) {
    if (buffer.empty()) {
        buffer = "";
        return;
    }
    tokens.push_back(Token(input.getLine(), input.getLinePos() - buffer.length(), TokenType::literal, buffer));
}
