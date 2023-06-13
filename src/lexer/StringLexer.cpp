#include "StringLexer.h"
#include "CharLexer.h"
#include "CodeLexer.h"

using namespace Lexing;
using namespace FileAccess;

StringLexer::StringLexer(std::list<Token>& tokens) : Lexer(tokens) {}

void StringLexer::tokenize(FileReader& input) {
    uint32_t startLinePos = input.getLinePos();
    char c;
    while (input.good()) {
        c = input.getch();
        switch (c) {
            case '"':
                processToken(input);
                tokens.push_back(Token(input.getLine(), input.getLinePos() - 1, TokenType::doubleQuote));
                return;
            case '$': {
                char n = input.getch();
                if (n == '{') {
                    processToken(input);
                    tokens.push_back(Token(input.getLine(), input.getLinePos() - 2, TokenType::dollarSign));
                    tokens.push_back(Token(input.getLine(), input.getLinePos() - 1, TokenType::braceLeft));
                    auto codeLexer = CodeLexer(tokens);
                    codeLexer.tokenize(input);
                } else {
                    buffer += c;
                    input.putch(n);
                }
                break;
            }
            case '\\': {
                processToken(input);
                input.putch(c);
                auto charLexer = CharLexer(tokens);
                charLexer.tokenize(input);
                break;
            }
            case '\n':
                if (!seekBlankSpace(input, startLinePos)) {
                    buffer += "\n";
                }
                break;
            default:
                buffer += c;
                break;
        }
    }
}

bool StringLexer::seekBlankSpace(FileReader& input, const uint32_t& startLinePos) {
    while (input.getLinePos() < startLinePos) {
        char e = input.getch();
        if (e == '\n') {
            input.putch('\n');
            break;
        } else if (e != ' ') {
            processToken(input);
            tokens.push_back(Token(input.getLine(), input.getLinePos(), TokenType::error, std::string(&e, 1)));
            return false;
        }
    }
    return true;
}

void StringLexer::processToken(FileAccess::FileReader& input) {
    if (buffer.empty()) {
        buffer = "";
        return;
    }
    tokens.push_back(Token(input.getLine(), input.getLinePos() - buffer.length(), TokenType::literal, buffer));
    buffer = "";
}
