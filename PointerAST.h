#pragma once

#include "AbstractSyntaxTree.h"
#include "Value.h"

class PointerAST : public AbstractSyntaxTree {
public:
    PointerAST(void* v, int lineno) {
        //最適化処理の時にintに変換
        this->value = new Value(v, lineno);
        this->lineno = lineno;
    }

    /*
    Value* Execute() {
        return new Value(value->GetPtr(), lineno);
    }
    */

private:
    Value* value;
    int lineno;

    ~PointerAST() {

    }

};