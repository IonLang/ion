#pragma once

#include "Lexer.h"
namespace Lexing {

class NumberLexer : public Lexer {
public:
    NumberLexer(uint32_t& line, uint32_t& linePos, std::list<Token>& tokens);
    ~NumberLexer() override {};

    void tokenize(std::istream &input) override;
};

}
