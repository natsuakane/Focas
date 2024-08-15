#pragma once

#include "AbstractSyntaxTree.h"
#include "Value.h"

class NumberAST : public AbstractSyntaxTree {
public:
    NumberAST(int v, int lineno) {
        this->value = new Value(v, lineno);
        this->lineno = lineno;
    }

    Value* Execute() {
        return new Value(value->GetInt(), lineno);
    }

private:
    Value* value;
    int lineno;

    ~NumberAST() {

    }

};