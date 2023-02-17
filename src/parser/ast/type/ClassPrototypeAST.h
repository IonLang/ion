#pragma once

#include <string>
#include <vector>
#include "parser/ast/BaseAST.h"
#include "parser/ast/ConstructorAST.h"
#include "parser/ast/meta/AccessModifierAST.h"
#include "parser/ast/meta/ClassModifierAST.h"

namespace AST {

class ClassPrototypeAST : public BaseAST {
public:
    const AccessModifierAST& accessModifier;
    const std::vector<ClassModifierAST>& classModifiers;
    const std::string& name;
    const std::vector<std::string>& superclasses;
    const ConstructorAST& primaryConstructor;
};

}
