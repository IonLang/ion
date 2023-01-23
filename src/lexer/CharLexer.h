#pragma once

#include "Lexer.h"
namespace Lexing {

class CharLexer : public Lexer {
public:
    CharLexer(uint32_t& line, uint32_t& linePos, std::list<Token>& tokens);
    ~CharLexer() override {};

    void tokenize(std::istream &input) override;
};

}  // namespace Lexing
