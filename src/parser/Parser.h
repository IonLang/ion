#pragma once

#include <list>
#include "lexer/token/Token.h"
#include "parser/ast/FileAST.h"

namespace Parsing {

class Parser {
    AST::FileAST parse(std::list<Lexing::Token> tokens);
};

}
