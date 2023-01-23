#include <fstream>
#include <iostream>
#include "lexer/CodeLexer.h"

using namespace Lexing;

int main() {
    std::ifstream testFile("test.ion", std::ios::in);
    uint32_t line = 0;
    uint32_t linePos = 0;
    std::list<Token> tokens;
    CodeLexer lexer = CodeLexer(line, linePos, tokens);
    lexer.tokenize(testFile);
    tokens.push_back(Token(lexer.currentLine(), lexer.currentLinePos(), TokenType::eof));
    testFile.close();
    std::string a[] = {
        "eof",
        "eol",
        "identifier",
        "literal",
        "braceLeft",
        "braceRight",
        "bracketLeft",
        "bracketRight",
        "parenLeft",
        "parenRight",
        "diamondLeft",
        "diamondRight",
        "doubleQuote",
        "singleQuote",
        "comma",
        "grave",
        "fun",
        "t_this",
        "t_if",
        "t_else",
        "t_switch",
        "t_case",
        "t_default",
        "t_break",
        "t_continue",
        "t_for",
        "t_while",
        "t_do",
        "t_return",
        "t_class",
        "t_enum",
        "t_private",
        "t_public",
        "t_protected",
        "t_throw",
        "t_try",
        "t_catch",
        "t_true",
        "t_false",
        "t_not",
        "t_and",
        "pipe",
        "shLeft",
        "shRight",
        "plus",
        "minus",
        "times",
        "divided",
        "power",
        "modulo",
        "andAssign",
        "pipeAssign",
        "shLeftAssign",
        "shRightAssign",
        "plusAssign",
        "minusAssign",
        "timesAssign",
        "dividedAssign",
        "powerAssign",
        "moduloAssign",
        "lessEquals",
        "greaterEquals",
        "assign",
        "equals",
        "equalsPointer",
        "notEquals",
        "arrow",
        "questionMark",
        "column",
        "import",
        "package",
        "var",
        "val",
        "by",
        "data",
        "immutable",
        "singleton",
        "interface",
        "sealed",
        "open",
        "abstract",
        "internal",
        "annotation",
        "at",
        "external",
        "constructor",
        "destructor",
        "final",
        "override",
        "dot",
        "null",
        "range",
        "rangeInclusive",
        "underscore",
        "in",
        "as",
        "is"
    };
    std::ofstream output("tokens.txt", std::ios::out);
    for (auto& i : tokens) {
        output.write(a[i.type()].data(), a[i.type()].length());
        output.write("\n", 1);
    }
    output.close();
    return 0;
}
