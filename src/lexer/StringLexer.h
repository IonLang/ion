#pragma once

#include "Lexer.h"

namespace Lexing {

class StringLexer : public Lexer {
public:
    StringLexer(uint32_t& line, uint32_t& linePos, std::list<Token>& tokens);
    ~StringLexer() override {};

    void tokenize(std::istream& input) override;
private:
    std::string buffer = "";
};

}  // namespace Lexing
