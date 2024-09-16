#pragma once

#include "AbstractSyntaxTree.h"
#include "Value.h"

class NumberAST : public AbstractSyntaxTree {
public:
    NumberAST(long v, int lineno) {
        this->value = new Value((long)v, lineno);
        this->lineno = lineno;
    }

    AbstractSyntaxTree* GetChild(int i) {
        throw std::runtime_error(TypeHasNoChildren("Number", lineno));
    }

    std::string OutputCode();

    bool DoesNeedSemicolon() {
        return true;
    }

private:
    Value* value;
    int lineno;

    ~NumberAST() {

    }

};

std::string NumberAST::OutputCode() {
    return std::to_string(value->GetLong());
}