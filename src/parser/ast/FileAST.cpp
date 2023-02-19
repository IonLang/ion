#include "FileAST.h"

using namespace AST;

FileAST::~FileAST() {
    for (auto& i : functions) {
        delete i;
    }
    for (auto& i : variables) {
        delete i;
    }
    for (auto& i : classes) {
        delete i;
    }
    for (auto& i : interfaces) {
        delete i;
    }
    for (auto& i : singletons) {
        delete i;
    }
    for (auto& i : annotations) {
        delete i;
    }
}
