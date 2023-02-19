#include "ClassAST.h"

using namespace AST;

ClassAST::~ClassAST() {
    for (auto& i : constructors) {
        delete i;
    }
    for (auto& i : properties) {
        delete i;
    }
    for (auto& i : methods) {
        delete i;
    }
    delete destructor;
}
