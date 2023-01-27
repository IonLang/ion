#include "StringLexer.h"
#include "CharLexer.h"
#include "CodeLexer.h"

using namespace Lexing;

StringLexer::StringLexer(uint32_t& line, uint32_t& linePos, std::list<Token>& tokens) : Lexer(line, linePos, tokens) {}

void StringLexer::tokenize(std::istream& input) {
    uint32_t startLinePos = linePos;
    char c;
    while (input.good()) {
        input.get(c);
        linePos++;
        switch (c) {
            case '"':
                processToken();
                tokens.push_back(Token(line, linePos - 1, TokenType::doubleQuote));
                return;
            case '$': {
                char n;
                input.get(n);
                linePos++;
                if (n == '{') {
                    processToken();
                    tokens.push_back(Token(line, linePos - 2, TokenType::dollarSign));
                    tokens.push_back(Token(line, linePos - 1, TokenType::braceLeft));
                    auto codeLexer = CodeLexer(line, linePos, tokens);
                    codeLexer.tokenize(input);
                } else {
                    buffer += c;
                    input.putback(n);
                    linePos--;
                }
                break;
            }
            case '\\': {
                processToken();
                input.putback(c);
                linePos--;
                auto charLexer = CharLexer(line, linePos, tokens);
                charLexer.tokenize(input);
                break;
            }
            case '\n':
                linePos = 0;
                line++;
                while (linePos < startLinePos) {
                    char e;
                    input.get(e);
                    linePos++;
                    if (e == '\n') {
                        input.putback('\n');
                        break;
                    } else if (e != ' ') {
                        throw std::exception();
                    }
                }
                buffer += "\n";
                break;
            default:
                buffer += c;
                break;
        }
    }
}

void StringLexer::processToken() {
    if (buffer.empty()) {
        buffer = "";
        return;
    }
    tokens.push_back(Token(line, linePos - buffer.length(), TokenType::literal, buffer));
    buffer = "";
}
