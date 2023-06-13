#include <algorithm>
#include <iostream>
#include "fileaccess/FileReader.h"
#include "lexer/CodeLexer.h"

using namespace Lexing;
using namespace FileAccess;

int main() {
    FileReader testFile("test.ion");
    std::list<Token> tokens;
    CodeLexer lexer = CodeLexer(tokens, true);
    lexer.tokenize(testFile);
    tokens.push_back(Token(testFile.getLine(), testFile.getLinePos(), TokenType::eof));
    std::ofstream output("tokens.txt");
    for (auto& i : tokens) {
        output.write(TokenTypeNames[i.type()].data(), TokenTypeNames[i.type()].length());
        if (i.type() == TokenType::literal || i.type() == TokenType::identifier || i.type() == TokenType::error) {
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
