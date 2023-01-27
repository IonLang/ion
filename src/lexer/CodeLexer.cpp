#include "CodeLexer.h"
#include "CharLexer.h"
#include "IdentifierLexer.h"
#include "NumberLexer.h"
#include "StringLexer.h"

using namespace Lexing;

CodeLexer::CodeLexer(uint32_t& line, uint32_t& linePos, std::list<Token>& tokens) : Lexer(line, linePos, tokens) {}

void CodeLexer::tokenize(std::istream& input) {
    char c;
    while (input.good()) {
        input.get(c);
        linePos++;
        switch (c) {
            case '{': {
                processToken();
                tokens.push_back(Token(line, linePos - 1, TokenType::braceLeft));
                auto codeLexer = CodeLexer(line, linePos, tokens);
                codeLexer.tokenize(input);
                break;
            }
            case '}':
                processToken();
                tokens.push_back(Token(line, linePos - 1, TokenType::braceRight));
                return;
            case '[':
                processToken();
                tokens.push_back(Token(line, linePos - 1, TokenType::bracketLeft));
                break;
            case ']':
                processToken();
                tokens.push_back(Token(line, linePos - 1, TokenType::bracketRight));
                break;
            case '(':
                processToken();
                tokens.push_back(Token(line, linePos - 1, TokenType::parenLeft));
                break;
            case ')':
                processToken();
                tokens.push_back(Token(line, linePos - 1, TokenType::parenRight));
                break;
            case '"': {
                processToken();
                tokens.push_back(Token(line, linePos - 1, TokenType::doubleQuote));
                auto stringLexer = StringLexer(line, linePos, tokens);
                stringLexer.tokenize(input);
                break;
            }
            case '\'': {
                processToken();
                tokens.push_back(Token(line, linePos - 1, TokenType::singleQuote));
                auto charLexer = CharLexer(line, linePos, tokens);
                charLexer.tokenize(input);
                break;
            }
            case ',':
                processToken();
                tokens.push_back(Token(line, linePos - 1, TokenType::comma));
                break;
            case '`': {
                processToken();
                tokens.push_back(Token(line, linePos - 1, TokenType::grave));
                auto identifierLexer = IdentifierLexer(line, linePos, tokens);
                identifierLexer.tokenize(input);
                break;
            }
            case '?':
                processToken();
                tokens.push_back(Token(line, linePos - 1, TokenType::questionMark));
                break;
            case ':':
                processToken();
                tokens.push_back(Token(line, linePos - 1, TokenType::column));
                break;
            case '@':
                processToken();
                tokens.push_back(Token(line, linePos - 1, TokenType::at));
                break;
            case ' ':
                processToken();
                break;
            case '.':
                processToken();
                char s;
                input.get(s);
                linePos++;
                if (s == '.') {
                    char t;
                    input.get(t);
                    linePos++;
                    if (t == '.') {
                        tokens.push_back(Token(line, linePos - 3, TokenType::rangeInclusive));
                    } else {
                        input.putback(t);
                        linePos--;
                        tokens.push_back(Token(line, linePos - 2, TokenType::range));
                    }
                } else {
                    input.putback(s);
                    linePos--;
                    tokens.push_back(Token(line, linePos - 1, TokenType::dot));
                }
                break;
            case '\n':
                processToken();
                if (!tokens.empty() && tokens.back().type() != TokenType::eol) {
                    tokens.push_back(Token(line, linePos - 1, TokenType::eol));
                }
                linePos = 0;
                line++;
                break;
            default:
                if (buffer.empty() && isdigit(c)) {
                    input.putback(c);
                    linePos--;
                    auto numberLexer = NumberLexer(line, linePos, tokens);
                    numberLexer.tokenize(input);
                    break;
                }
                buffer += c;
                break;
        }
    }
}

void CodeLexer::processToken() {
    if (buffer.empty()) {
        buffer = "";
        return;
    }
    if (buffer == "<") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::diamondLeft));
    else if (buffer == ">") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::diamondRight));
    else if (buffer == "fun") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::fun));
    else if (buffer == "if") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::t_if));
    else if (buffer == "else") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::t_else));
    else if (buffer == "switch") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::t_switch));
    else if (buffer == "case") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::t_case));
    else if (buffer == "default") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::t_default));
    else if (buffer == "break") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::t_break));
    else if (buffer == "continue") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::t_continue));
    else if (buffer == "for") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::t_for));
    else if (buffer == "while") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::t_while));
    else if (buffer == "do") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::t_do));
    else if (buffer == "return") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::t_return));
    else if (buffer == "class") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::t_class));
    else if (buffer == "enum") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::t_enum));
    else if (buffer == "private") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::t_private));
    else if (buffer == "public") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::t_public));
    else if (buffer == "protected") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::t_protected));
    else if (buffer == "throw") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::t_throw));
    else if (buffer == "try") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::t_try));
    else if (buffer == "catch") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::t_catch));
    else if (buffer == "!") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::t_not));
    else if (buffer == "&") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::t_and));
    else if (buffer == "^") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::t_xor));
    else if (buffer == "|") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::pipe));
    else if (buffer == "<<") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::shLeft));
    else if (buffer == ">>") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::shRight));
    else if (buffer == "+") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::plus));
    else if (buffer == "-") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::minus));
    else if (buffer == "*") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::times));
    else if (buffer == "/") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::divided));
    else if (buffer == "**") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::power));
    else if (buffer == "%") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::modulo));
    else if (buffer == "&=") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::andAssign));
    else if (buffer == "^=") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::xorAssign));
    else if (buffer == "|=") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::pipeAssign));
    else if (buffer == "<<=") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::shLeftAssign));
    else if (buffer == ">>=") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::shRightAssign));
    else if (buffer == "+=") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::plusAssign));
    else if (buffer == "-=") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::minusAssign));
    else if (buffer == "*=") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::timesAssign));
    else if (buffer == "/=") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::dividedAssign));
    else if (buffer == "**=") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::powerAssign));
    else if (buffer == "%=") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::moduloAssign));
    else if (buffer == "<=") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::lessEquals));
    else if (buffer == ">=") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::greaterEquals));
    else if (buffer == "=") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::assign));
    else if (buffer == "==") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::equals));
    else if (buffer == "===") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::equalsPointer));
    else if (buffer == "!=") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::notEquals));
    else if (buffer == "->") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::arrow));
    else if (buffer == "import") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::import));
    else if (buffer == "var") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::var));
    else if (buffer == "val") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::val));
    else if (buffer == "by") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::by));
    else if (buffer == "data") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::data));
    else if (buffer == "immutable") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::immutable));
    else if (buffer == "singleton") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::singleton));
    else if (buffer == "interface") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::interface));
    else if (buffer == "sealed") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::sealed));
    else if (buffer == "open") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::open));
    else if (buffer == "abstract") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::abstract));
    else if (buffer == "internal") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::internal));
    else if (buffer == "annotation") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::annotation));
    else if (buffer == "external") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::external));
    else if (buffer == "constructor") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::constructor));
    else if (buffer == "destructor") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::destructor));
    else if (buffer == "final") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::final));
    else if (buffer == "override") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::override));
    else if (buffer == "true") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::t_true));
    else if (buffer == "false") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::t_false));
    else if (buffer == "null") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::null));
    else if (buffer == "in") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::in));
    else if (buffer == "as") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::as));
    else if (buffer == "is") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::is));
    else if (buffer == "_") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::underscore));
    else if (buffer == "this") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::t_this));
    else if (buffer == "operator") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::t_operator));
    else if (buffer == "inline") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::t_inline));
    else if (buffer == "infix") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::infix));
    else if (buffer == "mutable") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::t_mutable));
    else if (buffer == "typedef") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::t_typedef));
    else if (buffer == "++") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::increment));
    else if (buffer == "--") tokens.push_back(Token(line, linePos - buffer.length(), TokenType::decrement));
    else tokens.push_back(Token(line, linePos - buffer.length(), TokenType::identifier, buffer));
    buffer = "";
}
