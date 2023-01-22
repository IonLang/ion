#pragma once

#include "ILexer.h"
namespace Lexing {

class CodeLexer : public ILexer {
public:
    CodeLexer(uint32_t line = 0, uint32_t linePos = 0);
    ~CodeLexer() override {};

    void tokenize(std::istream& input) override;
private:
    void processToken();
    std::string buffer = "";
};

}  // namespace Lexing
