#include <algorithm>
#include <fstream>
#include <iostream>
#include "lexer/CodeLexer.h"

using namespace Lexing;

int main() {
    std::ifstream testFile("test.ion");
    uint32_t line = 0;
    uint32_t linePos = 0;
    std::list<Token> tokens;
    CodeLexer lexer = CodeLexer(line, linePos, tokens);
    lexer.tokenize(testFile);
    tokens.push_back(Token(line, linePos, TokenType::eof));
    testFile.close();
    std::ofstream output("tokens.txt");
    for (auto& i : tokens) {
        output.write(TokenTypeNames[i.type()].data(), TokenTypeNames[i.type()].length());
        if (i.type() == TokenType::literal || i.type() == TokenType::identifier) {
            std::string value = i.value();
            std::replace(value.begin(), value.end(), '\n', '\\');
            std::string s = "\t\t" + value;
            output.write(s.c_str(), s.length());
        }
        output.write("\n", 1);
    }
    output.close();
    return 0;
}
