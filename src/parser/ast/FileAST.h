#pragma once

#include <string>
#include <vector>
#include "BaseAST.h"
#include "FunctionAST.h"
#include "VariableAST.h"
#include "parser/ast/type/AnnotationAST.h"
#include "parser/ast/type/ClassAST.h"
#include "parser/ast/type/InterfaceAST.h"
#include "parser/ast/type/SingletonAST.h"

namespace AST {

class FileAST : public BaseAST {
public:
    ~FileAST() override;

    std::vector<std::string> imports;
    std::vector<FunctionAST*> functions;
    std::vector<VariableAST*> variables;
    std::vector<ClassAST*> classes;
    std::vector<InterfaceAST*> interfaces;
    std::vector<SingletonAST*> singletons;
    std::vector<AnnotationAST*> annotations;
};

}
