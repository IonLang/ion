#include "NumberLexer.h"

using namespace Lexing;

NumberLexer::NumberLexer(uint32_t& line, uint32_t& linePos) : Lexer(line, linePos) {}

void NumberLexer::tokenize(std::istream& input) {
    std::string buffer = "";
    bool comma = false;
    char mode = 'd';
    char c;
    input.get(c);
    while (input.good()) {
        input.get(c);
        if (isdigit(c)) {
            buffer += c;
        } else if (c == '.' && !comma) {
            comma = true;
        } else if (buffer == "0" && (c == 'x' || c == 'b')) {
            buffer += c;
            mode = c;
        }
    }
}
