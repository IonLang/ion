#include "AnnotationAST.h"

using namespace AST;

AnnotationAST::AnnotationAST(const std::string& name, const std::vector<ParameterAST>& params) : name(name), params(params) {}
