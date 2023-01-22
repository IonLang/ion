#include "CodeLexer.h"
#include "CharLexer.h"
#include "IdentifierLexer.h"
#include "StringLexer.h"

using namespace Lexing;

CodeLexer::CodeLexer(uint32_t& line, uint32_t& linePos) : Lexer(line, linePos) {}

void CodeLexer::tokenize(std::istream& input) {
    char c;
    while (!(input.get(c), input.good())) {
        linePos++;
        switch (c) {
            case '{': {
                processToken();
                list.push_back(Token(line, linePos, TokenType::braceLeft));
                auto codeLexer = CodeLexer(line, linePos);
                codeLexer.tokenize(input);
                for (const auto& i : codeLexer.tokens()) {
                    list.push_back(i);
                }
                break;
            }
            case '}':
                processToken();
                list.push_back(Token(line, linePos, TokenType::braceRight));
                return;
            case '[':
                processToken();
                list.push_back(Token(line, linePos, TokenType::bracketLeft));
                break;
            case ']':
                processToken();
                list.push_back(Token(line, linePos, TokenType::bracketRight));
                break;
            case '(':
                processToken();
                list.push_back(Token(line, linePos, TokenType::parenLeft));
                break;
            case ')':
                processToken();
                list.push_back(Token(line, linePos, TokenType::parenRight));
                break;
            case '"': {
                processToken();
                list.push_back(Token(line, linePos, TokenType::doubleQuote));
                auto stringLexer = StringLexer(line, linePos);
                stringLexer.tokenize(input);
                break;
            }
            case '\'': {
                processToken();
                list.push_back(Token(line, linePos, TokenType::singleQuote));
                auto charLexer = CharLexer(line, linePos);
                charLexer.tokenize(input);
                break;
            }
            case ',':
                processToken();
                list.push_back(Token(line, linePos, TokenType::comma));
                break;
            case '.':
                processToken();
                list.push_back(Token(line, linePos, TokenType::dot));
                break;
            case '`': {
                processToken();
                list.push_back(Token(line, linePos, TokenType::grave));
                auto identifierLexer = IdentifierLexer(line, linePos);
                identifierLexer.tokenize(input);
                for (const auto& i : identifierLexer.tokens()) {
                    list.push_back(i);
                }
                break;
            }
            case '?':
                processToken();
                list.push_back(Token(line, linePos, TokenType::questionMark));
                break;
            case ':':
                processToken();
                list.push_back(Token(line, linePos, TokenType::column));
                break;
            case '@':
                processToken();
                list.push_back(Token(line, linePos, TokenType::at));
                break;
            case ' ':
                processToken();
                break;
            case '\n':
                linePos = 0;
                line++;
                processToken();
                break;
            default:
                buffer += c;
                break;
        }
    }
}

void CodeLexer::processToken() {
    if (!buffer.empty()) {
        if (buffer == "<") list.push_back(Token(line, linePos - buffer.length(), TokenType::diamondLeft));
        else if (buffer == ">") list.push_back(Token(line, linePos - buffer.length(), TokenType::diamondRight));
        else if (buffer == "fun") list.push_back(Token(line, linePos - buffer.length(), TokenType::fun));
        else if (buffer == "if") list.push_back(Token(line, linePos - buffer.length(), TokenType::t_if));
        else if (buffer == "else") list.push_back(Token(line, linePos - buffer.length(), TokenType::t_else));
        else if (buffer == "switch") list.push_back(Token(line, linePos - buffer.length(), TokenType::t_switch));
        else if (buffer == "case") list.push_back(Token(line, linePos - buffer.length(), TokenType::t_case));
        else if (buffer == "break") list.push_back(Token(line, linePos - buffer.length(), TokenType::t_break));
        else if (buffer == "continue") list.push_back(Token(line, linePos - buffer.length(), TokenType::t_continue));
        else if (buffer == "for") list.push_back(Token(line, linePos - buffer.length(), TokenType::t_for));
        else if (buffer == "while") list.push_back(Token(line, linePos - buffer.length(), TokenType::t_while));
        else if (buffer == "do") list.push_back(Token(line, linePos - buffer.length(), TokenType::t_do));
        else if (buffer == "return") list.push_back(Token(line, linePos - buffer.length(), TokenType::t_return));
        else if (buffer == "class") list.push_back(Token(line, linePos - buffer.length(), TokenType::t_class));
        else if (buffer == "enum") list.push_back(Token(line, linePos - buffer.length(), TokenType::t_enum));
        else if (buffer == "private") list.push_back(Token(line, linePos - buffer.length(), TokenType::t_private));
        else if (buffer == "public") list.push_back(Token(line, linePos - buffer.length(), TokenType::t_public));
        else if (buffer == "protected") list.push_back(Token(line, linePos - buffer.length(), TokenType::t_protected));
        else if (buffer == "throw") list.push_back(Token(line, linePos - buffer.length(), TokenType::t_throw));
        else if (buffer == "try") list.push_back(Token(line, linePos - buffer.length(), TokenType::t_try));
        else if (buffer == "catch") list.push_back(Token(line, linePos - buffer.length(), TokenType::t_catch));
        else if (buffer == "!") list.push_back(Token(line, linePos - buffer.length(), TokenType::t_not));
        else if (buffer == "&") list.push_back(Token(line, linePos - buffer.length(), TokenType::t_and));
        else if (buffer == "|") list.push_back(Token(line, linePos - buffer.length(), TokenType::pipe));
        else if (buffer == "<<") list.push_back(Token(line, linePos - buffer.length(), TokenType::shLeft));
        else if (buffer == ">>") list.push_back(Token(line, linePos - buffer.length(), TokenType::shRight));
        else if (buffer == "+") list.push_back(Token(line, linePos - buffer.length(), TokenType::plus));
        else if (buffer == "-") list.push_back(Token(line, linePos - buffer.length(), TokenType::minus));
        else if (buffer == "*") list.push_back(Token(line, linePos - buffer.length(), TokenType::times));
        else if (buffer == "/") list.push_back(Token(line, linePos - buffer.length(), TokenType::divided));
        else if (buffer == "**") list.push_back(Token(line, linePos - buffer.length(), TokenType::power));
        else if (buffer == "%") list.push_back(Token(line, linePos - buffer.length(), TokenType::modulo));
        else if (buffer == "&=") list.push_back(Token(line, linePos - buffer.length(), TokenType::andAssign));
        else if (buffer == "|=") list.push_back(Token(line, linePos - buffer.length(), TokenType::pipeAssign));
        else if (buffer == "<<=") list.push_back(Token(line, linePos - buffer.length(), TokenType::shLeftAssign));
        else if (buffer == ">>=") list.push_back(Token(line, linePos - buffer.length(), TokenType::shRightAssign));
        else if (buffer == "+=") list.push_back(Token(line, linePos - buffer.length(), TokenType::plusAssign));
        else if (buffer == "-=") list.push_back(Token(line, linePos - buffer.length(), TokenType::minusAssign));
        else if (buffer == "*=") list.push_back(Token(line, linePos - buffer.length(), TokenType::timesAssign));
        else if (buffer == "/=") list.push_back(Token(line, linePos - buffer.length(), TokenType::dividedAssign));
        else if (buffer == "**=") list.push_back(Token(line, linePos - buffer.length(), TokenType::powerAssign));
        else if (buffer == "%=") list.push_back(Token(line, linePos - buffer.length(), TokenType::moduloAssign));
        else if (buffer == "<=") list.push_back(Token(line, linePos - buffer.length(), TokenType::lessEquals));
        else if (buffer == ">=") list.push_back(Token(line, linePos - buffer.length(), TokenType::greaterEquals));
        else if (buffer == "=") list.push_back(Token(line, linePos - buffer.length(), TokenType::assign));
        else if (buffer == "==") list.push_back(Token(line, linePos - buffer.length(), TokenType::equals));
        else if (buffer == "!=") list.push_back(Token(line, linePos - buffer.length(), TokenType::notEquals));
        else if (buffer == "->") list.push_back(Token(line, linePos - buffer.length(), TokenType::arrow));
        else if (buffer == "import") list.push_back(Token(line, linePos - buffer.length(), TokenType::import));
        else if (buffer == "package") list.push_back(Token(line, linePos - buffer.length(), TokenType::package));
        else if (buffer == "var") list.push_back(Token(line, linePos - buffer.length(), TokenType::var));
        else if (buffer == "val") list.push_back(Token(line, linePos - buffer.length(), TokenType::val));
        else if (buffer == "by") list.push_back(Token(line, linePos - buffer.length(), TokenType::by));
        else if (buffer == "data") list.push_back(Token(line, linePos - buffer.length(), TokenType::data));
        else if (buffer == "immutable") list.push_back(Token(line, linePos - buffer.length(), TokenType::immutable));
        else if (buffer == "singleton") list.push_back(Token(line, linePos - buffer.length(), TokenType::singleton));
        else if (buffer == "interface") list.push_back(Token(line, linePos - buffer.length(), TokenType::interface));
        else if (buffer == "sealed") list.push_back(Token(line, linePos - buffer.length(), TokenType::sealed));
        else if (buffer == "open") list.push_back(Token(line, linePos - buffer.length(), TokenType::open));
        else if (buffer == "abstract") list.push_back(Token(line, linePos - buffer.length(), TokenType::abstract));
        else if (buffer == "internal") list.push_back(Token(line, linePos - buffer.length(), TokenType::internal));
        else if (buffer == "annotation") list.push_back(Token(line, linePos - buffer.length(), TokenType::annotation));
        else if (buffer == "external") list.push_back(Token(line, linePos - buffer.length(), TokenType::external));
        else if (buffer == "constructor") list.push_back(Token(line, linePos - buffer.length(), TokenType::constructor));
        else if (buffer == "destructor") list.push_back(Token(line, linePos - buffer.length(), TokenType::destructor));
        else if (buffer == "final") list.push_back(Token(line, linePos - buffer.length(), TokenType::final));
        else if (buffer == "override") list.push_back(Token(line, linePos - buffer.length(), TokenType::override));
    }
    buffer = "";
}
