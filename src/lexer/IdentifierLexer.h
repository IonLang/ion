#pragma once

#include "Lexer.h"

namespace Lexing {

class IdentifierLexer : public Lexer {
public:
    IdentifierLexer(std::list<Token>& tokens);
    ~IdentifierLexer() override {};

    void tokenize(FileAccess::FileReader& input) override;
};

}
