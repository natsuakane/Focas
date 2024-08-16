#pragma once

#include "AbstractSyntaxTree.h"
#include "Value.h"

class NumberAST : public AbstractSyntaxTree {
public:
    NumberAST(long v, int lineno) {
        //最適化処理の時にintに変換
        this->value = new Value((long)v, lineno);
        this->lineno = lineno;
    }

    Value* Execute() {
        return new Value(value->GetLong(), lineno);
    }

private:
    Value* value;
    int lineno;

    ~NumberAST() {

    }

};