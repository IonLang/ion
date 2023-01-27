#include "CharLexer.h"

using namespace Lexing;

CharLexer::CharLexer(uint32_t& line, uint32_t& linePos, std::list<Token>& tokens) : Lexer(line, linePos, tokens) {}

void CharLexer::tokenize(std::istream& input) {
    char c;
    input.get(c);
    linePos++;
    if (c == '\\') {
        char n;
        input.get(n);
        linePos++;
        switch (n) {
            case '\'':
                tokens.push_back(Token(line, linePos - 2, TokenType::escSingleQuote));
                break;
            case '"':
                tokens.push_back(Token(line, linePos - 2, TokenType::escDoubleQuote));
                break;
            case '\\':
                tokens.push_back(Token(line, linePos - 2, TokenType::escBackSlash));
                break;
            case 'n':
                tokens.push_back(Token(line, linePos - 2, TokenType::escNewLine));
                break;
            case 'r':
                tokens.push_back(Token(line, linePos - 2, TokenType::escCarriageReturn));
                break;
            case 't':
                tokens.push_back(Token(line, linePos - 2, TokenType::escTab));
                break;
            case 'b':
                tokens.push_back(Token(line, linePos - 2, TokenType::escBackspace));
                break;
            case 'f':
                tokens.push_back(Token(line, linePos - 2, TokenType::escFormFeed));
                break;
            case 'a':
                tokens.push_back(Token(line, linePos - 2, TokenType::escBell));
                break;
            case '$':
                tokens.push_back(Token(line, linePos - 2, TokenType::escDollarSign));
                break;
            case '0': {
                char l;
                char r;
                input.get(l);
                input.get(r);
                linePos += 2;
                if (l >= '0' && l <= '8' && r >= '0' && r <= '8') {
                    std::string num = "";
                    num += l;
                    num += r;
                    tokens.push_back(Token(line, linePos - 4, TokenType::escOctal, num));
                } else {
                    throw std::exception();
                }
                break;
            }
            case 'x': {
                char l;
                char r;
                input.get(l);
                input.get(r);
                linePos += 2;
                if ((isdigit(l) || (l >= '0' && l <= '6')) && (isdigit(r) || (r >= '0' && r <= '6'))) {
                    std::string num = "";
                    num += l;
                    num += r;
                    tokens.push_back(Token(line, linePos - 4, TokenType::escHex, num));
                } else {
                    throw std::exception();
                }
                break;
            }
            case 'u': {
                char n0;
                char n1;
                char n2;
                char n3;
                input.get(n0);
                input.get(n1);
                input.get(n2);
                input.get(n3);
                linePos += 4;
                if ((isdigit(n0) || (n0 >= '0' && n0 <= '6'))
                    && (isdigit(n1) || (n1 >= '0' && n1 <= '6'))
                    && (isdigit(n2) || (n2 >= '0' && n2 <= '6'))
                    && (isdigit(n3) || (n3 >= '0' && n3 <= '6'))) {
                    std::string num = "";
                    num += n0;
                    num += n1;
                    num += n2;
                    num += n3;
                    tokens.push_back(Token(line, linePos - 6, TokenType::escUnicode, num));
                } else {
                    throw std::exception();
                }
                break;
            }
        }
    } else {
        tokens.push_back(Token(line, linePos - 1, TokenType::literal, std::string({c})));
    }
}
