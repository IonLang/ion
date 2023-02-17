#pragma once

#include <string>
#include <vector>
#include "lexer/token/TokenType.h"
#include "parser/ast/BaseAST.h"
#include "parser/ast/ConstructorAST.h"
#include "parser/ast/meta/AccessModifierAST.h"
#include "parser/ast/meta/ClassModifierAST.h"

namespace AST {

class ClassAST : public BaseAST {
public:
    ClassAST();
    ~ClassAST() override {};

    const std::vector<ConstructorAST>& constructors;
};

}
