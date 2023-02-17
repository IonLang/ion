#include "NumberLexer.h"
#include <iostream>

using namespace Lexing;
using namespace FileAccess;

NumberLexer::NumberLexer(std::list<Token>& tokens) : Lexer(tokens) {}

void NumberLexer::tokenize(FileReader& input) {
    std::string buffer = "";
    bool comma = false;
    char mode = 'd';
    char c = input.getch();
    if (c == '0') {
        if (!input.good()) {
            tokens.push_back(Token(input.getLine(), input.getLinePos() - 1, TokenType::literal, "0"));
            return;
        }
        char m = input.getch();
        switch (m) {
            case 'b':
            case 'x':
                mode = m;
                buffer += m;
                break;
            case '\n':
                tokens.push_back(Token(input.getLine(), input.getLinePos() - 2, TokenType::literal, "0"));
                tokens.push_back(Token(input.getLine(), input.getLinePos() - 1, TokenType::eol));
                return;
            case '.':
                comma = true;
                c = input.getch();
                if (!isdigit(c)) {
                    input.putch(c);
                    tokens.push_back(Token(input.getLine(), input.getLinePos() - 1, TokenType::dot));
                    return;
                }
                buffer += m;
                buffer += c;
                break;
            case '_':
                break;
            default:
                if (!isdigit(m)) {
                    tokens.push_back(Token(input.getLine(), input.getLinePos() - 2, TokenType::literal, "0"));
                    return;
                }
                buffer += m;
                break;
        }
    } else if (isdigit(c)) {
        buffer += c;
    }
    while (input.good()) {
        c = input.getch();
        if (c == '_') {
            continue;
        }
        switch (mode) {
            case 'd':
                if (isdigit(c)) {
                    buffer += c;
                    continue;
                }
                input.putch(c);
                break;
            case 'x':
                if (isdigit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F')) {
                    buffer += c;
                    continue;
                }
                input.putch(c);
                break;
            case 'b':
                if (c == '0' || c == '1') {
                    buffer += c;
                    continue;
                }
                input.putch(c);
                break;
        }
        tokens.push_back(Token(input.getLine(), input.getLinePos() - buffer.length(), TokenType::literal, buffer));
        return;
    }
}
