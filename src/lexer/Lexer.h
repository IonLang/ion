#pragma once

#include <istream>
#include <list>
#include "fileaccess/FileReader.h"
#include "lexer/token/Token.h"

namespace Lexing {

class Lexer {
public:
    Lexer(std::list<Token>& tokens);
    virtual ~Lexer() {};

    virtual void tokenize(FileAccess::FileReader& input) = 0;
protected:
    std::list<Token>& tokens;
};

}  // namespace Lexing
