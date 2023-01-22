#pragma once

#include "ILexer.h"

namespace Lexing {

class StringLexer : public ILexer {
public:
    StringLexer(uint32_t line, uint32_t linePos);
    ~StringLexer() override {};

    void tokenize(std::istream& input) override;
private:
    std::string buffer = "";
};

}  // namespace Lexing
