#pragma once

#include "Lexer.h"
namespace Lexing {

class IdentifierLexer : public Lexer {
public:
    IdentifierLexer(uint32_t& line, uint32_t& linePos);
    ~IdentifierLexer() override {};

    void tokenize(std::istream &input) override;
};

}
