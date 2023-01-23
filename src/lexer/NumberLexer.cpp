#include "NumberLexer.h"
#include <iostream>

using namespace Lexing;

NumberLexer::NumberLexer(uint32_t& line, uint32_t& linePos, std::list<Token>& tokens) : Lexer(line, linePos, tokens) {}

void NumberLexer::tokenize(std::istream& input) {
    std::string buffer = "";
    bool comma = false;
    char mode = 'd';
    char c;
    input.get(c);
    linePos++;
    if (c == '0') {
        if (!input.good()) {
            tokens.push_back(Token(line, linePos - 1, TokenType::literal, "0"));
            return;
        }
        char m;
        input.get(m);
        switch (m) {
            case 'b':
            case 'x':
                mode = m;
                buffer += m;
                break;
            case '\n':
                tokens.push_back(Token(line, linePos - 2, TokenType::literal, "0"));
                tokens.push_back(Token(line, linePos - 1, TokenType::eol));
                linePos = 0;
                line++;
                return;
            case '.':
                comma = true;
                input.get(c);
                if (!isdigit(c)) {
                    input.putback(c);
                    tokens.push_back(Token(line, linePos - 1, TokenType::dot));
                    return;
                }
                buffer += m;
                buffer += c;
                linePos++;
                break;
            case '_':
                break;
            default:
                if (!isdigit(m)) {
                    tokens.push_back(Token(line, linePos - 2, TokenType::literal, "0"));
                    return;
                }
                buffer += m;
                break;
        }
    } else if (isdigit(c)) {
        buffer += c;
    }
    while (input.good()) {
        input.get(c);
        linePos++;
        if (c == '_') {
            continue;
        }
        switch (mode) {
            case 'd':
                if (isdigit(c)) {
                    buffer += c;
                    break;
                }
                input.putback(c);
                linePos--;
            case 'x':
                if (isdigit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F')) {
                    buffer += c;
                    break;
                }
                input.putback(c);
                linePos--;
            case 'b':
                if (c == '0' || c == '1') {
                    buffer += c;
                    break;
                }
                input.putback(c);
                linePos--;
            default:
                tokens.push_back(Token(line, linePos - buffer.length(), TokenType::literal, buffer));
                return;
        }
    }
}
