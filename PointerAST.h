#pragma once

#include "AbstractSyntaxTree.h"
#include "Value.h"

class PointerAST : public AbstractSyntaxTree {
public:
    PointerAST(void* v, int lineno) {
        this->value = new Value(v, lineno);
        this->lineno = lineno;
    }

private:
    Value* value;
    int lineno;

    ~PointerAST() {

    }

};