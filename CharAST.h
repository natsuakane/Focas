#pragma once

#include "AbstractSyntaxTree.h"
#include "Value.h"

class CharAST : public AbstractSyntaxTree {
public:
    CharAST(char v, int lineno) {
        this->value = new Value(v, lineno);
        this->lineno = lineno;
    }

    /*
    Value* Execute() {
        return new Value(value->GetChar(), lineno);
    }
    */

private:
    Value* value;
    int lineno;

    ~CharAST() {

    }

};