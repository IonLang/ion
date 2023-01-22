#pragma once

#include "ILexer.h"
namespace Lexing {

class IdentifierLexer : public ILexer {
public:
    ~IdentifierLexer() override {};

    std::list<Token> tokenize(std::istream &input) override;
};

}
