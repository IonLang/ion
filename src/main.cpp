#include <fstream>
#include <iostream>
#include "lexer/CodeLexer.h"

using namespace Lexing;

int main() {
    std::ifstream testFile("test.ion", std::ios::in);
    uint32_t line = 0;
    uint32_t linePos = 0;
    CodeLexer lexer = CodeLexer(line, linePos);
    lexer.tokenize(testFile);
    std::list<Token> tokens = lexer.tokens();
    tokens.push_back(Token(lexer.currentLine(), lexer.currentLinePos(), TokenType::eof));
    testFile.close();
    return 0;
}
