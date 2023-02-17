#pragma once

#include "Lexer.h"

namespace Lexing {

class CodeLexer : public Lexer {
public:
    CodeLexer(std::list<Token>& tokens);
    ~CodeLexer() override {};

    void tokenize(FileAccess::FileReader& input) override;
private:
    void processToken(FileAccess::FileReader& input);
    std::string buffer = "";
};

}  // namespace Lexing
