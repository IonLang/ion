#pragma once

#include "Lexer.h"
namespace Lexing {

class CodeLexer : public Lexer {
public:
    CodeLexer(uint32_t& line, uint32_t& linePos, std::list<Token>& tokens);
    ~CodeLexer() override {};

    void tokenize(std::istream& input) override;
private:
    void processToken();
    std::string buffer = "";
};

}  // namespace Lexing
