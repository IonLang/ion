#pragma once

#include "Lexer.h"

namespace Lexing {

class StringLexer : public Lexer {
public:
    StringLexer(std::list<Token>& tokens);
    ~StringLexer() override {};

    void tokenize(FileAccess::FileReader& input) override;
private:
    bool seekBlankSpace(FileAccess::FileReader& input, const uint32_t& startLinePos);
    void processToken(FileAccess::FileReader& input);
    std::string buffer = "";
};

}  // namespace Lexing
