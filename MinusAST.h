#pragma once

#include "AbstractSyntaxTree.h"
#include "Value.h"

class PlusAST : public AbstractSyntaxTree {
public:
    PlusAST(AbstractSyntaxTree* tree1, AbstractSyntaxTree* tree2, int lineno) {
        //最適化処理の時にintに変換
        this->tree1 = tree1;
        this->tree2 = tree2;
        this->lineno = lineno;
    }

    Value* Execute() {
        Value* value1 = tree1->Execute();
        Value* value2 = tree2->Execute();

        if(value1->GetValueType() == IntNum && value2->GetValueType() == IntNum) {
            return new Value(value1->GetInt() - value2->GetInt(), lineno);
        }
        else if(value1->GetValueType() == IntNum && value2->GetValueType() == LongNum) {
            return new Value(value1->GetInt() - value2->GetLong(), lineno);
        }
        else if(value1->GetValueType() == LongNum && value2->GetValueType() == IntNum) {
            return new Value(value1->GetLong() - value2->GetInt(), lineno);
        }
        else if(value1->GetValueType() == LongNum && value2->GetValueType() == LongNum) {
            return new Value(value1->GetLong() - value2->GetLong(), lineno);
        }

        else if(value1->GetValueType() == FloatNum && value2->GetValueType() == FloatNum) {
            return new Value(value1->GetFloat() - value2->GetFloat(), lineno);
        }
        else if(value1->GetValueType() == FloatNum && value2->GetValueType() == DoubleNum) {
            return new Value(value1->GetFloat() - value2->GetDouble(), lineno);
        }
        else if(value1->GetValueType() == DoubleNum && value2->GetValueType() == FloatNum) {
            return new Value(value1->GetDouble() - value2->GetFloat(), lineno);
        }
        else if(value1->GetValueType() == DoubleNum && value2->GetValueType() == DoubleNum) {
            return new Value(value1->GetDouble() - value2->GetDouble(), lineno);
        }

        else {
            throw std::runtime_error(UnsuitableTypeWithOperator("+", ValueTypeNames[value1->GetValueType()], lineno));
        }
    }

private:
    AbstractSyntaxTree* tree1;
    AbstractSyntaxTree* tree2;
    int lineno;

    ~PlusAST() {

    }

};