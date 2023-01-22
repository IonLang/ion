#include "CodeLexer.h"

using namespace Lexing;

CodeLexer::CodeLexer(uint32_t line, uint32_t linePos) : ILexer(line, linePos) {}

void CodeLexer::tokenize(std::istream& input) {
    char c;
    while (!(input.get(c), input.good())) {
        buffer += c;
        switch (c) {
            case ' ':
            case '\n':
                linePos = 0;
                line++;
                processToken();
                break;
            default:
                linePos++;
                buffer += c;
                break;
        }
    }
}

void CodeLexer::processToken() {
}
