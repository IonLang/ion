#include "CharLexer.h"

using namespace Lexing;
using namespace FileAccess;

CharLexer::CharLexer(std::list<Token>& tokens) : Lexer(tokens) {}

void CharLexer::tokenize(FileReader& input) {
    char c = input.getch();
    if (c == '\\') {
        char n = input.getch();
        switch (n) {
            case '\'':
                tokens.push_back(Token(input.getLine(), input.getLinePos() - 2, TokenType::escSingleQuote));
                break;
            case '"':
                tokens.push_back(Token(input.getLine(), input.getLinePos() - 2, TokenType::escDoubleQuote));
                break;
            case '\\':
                tokens.push_back(Token(input.getLine(), input.getLinePos() - 2, TokenType::escBackSlash));
                break;
            case 'n':
                tokens.push_back(Token(input.getLine(), input.getLinePos() - 2, TokenType::escNewLine));
                break;
            case 'r':
                tokens.push_back(Token(input.getLine(), input.getLinePos() - 2, TokenType::escCarriageReturn));
                break;
            case 't':
                tokens.push_back(Token(input.getLine(), input.getLinePos() - 2, TokenType::escTab));
                break;
            case 'b':
                tokens.push_back(Token(input.getLine(), input.getLinePos() - 2, TokenType::escBackspace));
                break;
            case 'f':
                tokens.push_back(Token(input.getLine(), input.getLinePos() - 2, TokenType::escFormFeed));
                break;
            case 'a':
                tokens.push_back(Token(input.getLine(), input.getLinePos() - 2, TokenType::escBell));
                break;
            case '$':
                tokens.push_back(Token(input.getLine(), input.getLinePos() - 2, TokenType::escDollarSign));
                break;
            case '0': {
                char l = input.getch();
                char r = input.getch();
                if (l >= '0' && l <= '8' && r >= '0' && r <= '8') {
                    std::string num = "";
                    num += l;
                    num += r;
                    tokens.push_back(Token(input.getLine(), input.getLinePos() - 4, TokenType::escOctal, num));
                } else {
                    throw std::exception();
                }
                break;
            }
            case 'x': {
                char l = input.getch();
                char r = input.getch();
                if ((isdigit(l) || (l >= '0' && l <= '6')) && (isdigit(r) || (r >= '0' && r <= '6'))) {
                    std::string num = "";
                    num += l;
                    num += r;
                    tokens.push_back(Token(input.getLine(), input.getLinePos() - 4, TokenType::escHex, num));
                } else {
                    throw std::exception();
                }
                break;
            }
            case 'u': {
                char n0 = input.getch();
                char n1 = input.getch();
                char n2 = input.getch();
                char n3 = input.getch();
                if ((isdigit(n0) || (n0 >= '0' && n0 <= '6'))
                    && (isdigit(n1) || (n1 >= '0' && n1 <= '6'))
                    && (isdigit(n2) || (n2 >= '0' && n2 <= '6'))
                    && (isdigit(n3) || (n3 >= '0' && n3 <= '6'))) {
                    std::string num = "";
                    num += n0;
                    num += n1;
                    num += n2;
                    num += n3;
                    tokens.push_back(Token(input.getLine(), input.getLinePos() - 6, TokenType::escUnicode, num));
                } else {
                    throw std::exception();
                }
                break;
            }
        }
    } else {
        tokens.push_back(Token(input.getLine(), input.getLinePos() - 1, TokenType::literal, std::string({c})));
    }
}
