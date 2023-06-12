#pragma once

#include "Lexer.h"

namespace Lexing {

class NumberLexer : public Lexer {
public:
    NumberLexer(std::list<Token>& tokens);
    ~NumberLexer() override {};

    void tokenize(FileAccess::FileReader& input) override;
private:
    std::string buffer = "";
    void processToken(FileAccess::FileReader& input);
};

}
