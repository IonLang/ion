#pragma once

#include <string>
#include <vector>
#include "lexer/token/TokenType.h"
#include "parser/ast/BaseAST.h"
#include "parser/ast/ConstructorAST.h"
#include "parser/ast/DestructorAST.h"
#include "parser/ast/FunctionAST.h"
#include "parser/ast/PropertyAST.h"
#include "parser/ast/meta/AccessModifierAST.h"
#include "parser/ast/meta/ClassModifierAST.h"

namespace AST {

class ClassAST : public BaseAST {
public:
    ~ClassAST() override;

    std::vector<ConstructorAST*> constructors;
    DestructorAST* destructor;
    std::vector<PropertyAST*> properties;
    std::vector<FunctionAST*> methods;
};

}
