#pragma once

#include "AbstractSyntaxTree.h"
#include "Value.h"
#include "IdentifierAST.h"
#include "CodeAST.h"

class ElifAST : public AbstractSyntaxTree {
public:
    ElifAST(AbstractSyntaxTree* expression, CodeAST* block, int lineno) {
        this->expression = expression;
        this->block = block;
        this->lineno = lineno;
    }

    AbstractSyntaxTree* GetChild(int i) {
        if(i == 0) return expression;
        if(i == 1) return block;

        throw std::runtime_error(TypeHasNoChildrenMoreThan("ElifAST", 2, lineno));
    }

    std::string OutputCode();

private:
    AbstractSyntaxTree* expression;
    CodeAST* block;
    int lineno;

    ~ElifAST() {

    }

};

std::string ElifAST::OutputCode() {
    return "else if(" + expression->OutputCode() + ") {\n" + block->OutputCode() + "}";
}