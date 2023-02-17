#pragma once

#include "Lexer.h"

namespace Lexing {

class CharLexer : public Lexer {
public:
    CharLexer(std::list<Token>& tokens);
    ~CharLexer() override {};

    void tokenize(FileAccess::FileReader& input) override;
};

}  // namespace Lexing
