#pragma once

#include "AbstractSyntaxTree.h"
#include "Value.h"

class FloatNumberAST : public AbstractSyntaxTree {
public:
    FloatNumberAST(double v, int lineno) {
        //最適化処理の時にfloatに変換
        this->value = new Value(v, lineno);
        this->lineno = lineno;
    }
    
    /*
    Value* Execute() {
        return new Value(value->GetDouble(), lineno);
    }
    */

private:
    Value* value;
    int lineno;

    ~FloatNumberAST() {

    }

};