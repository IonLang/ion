#pragma once

#include <string>
#include <vector>
#include "parser/ast/BaseAST.h"
#include "parser/ast/ParameterAST.h"

namespace AST {

class AnnotationAST : public BaseAST {
public:
    AnnotationAST(const std::string& name, const std::vector<ParameterAST>& params);
    ~AnnotationAST() override {};

    const std::string& name;
    const std::vector<ParameterAST>& params;
};

}
