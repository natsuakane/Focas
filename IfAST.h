#pragma once

#include "AbstractSyntaxTree.h"
#include "Value.h"
#include "IdentifierAST.h"
#include "CodeAST.h"

class IfAST : public AbstractSyntaxTree {
public:
    IfAST(AbstractSyntaxTree* expression, CodeAST* block, int lineno) {
        this->expression = expression;
        this->block = block;
        this->lineno = lineno;
    }

    AbstractSyntaxTree* GetChild(int i) {
        if(i == 0) return expression;
        if(i == 1) return block;

        throw std::runtime_error(TypeHasNoChildrenMoreThan("IfAST", 2, lineno));
    }

    std::string OutputCode();

private:
    AbstractSyntaxTree* expression;
    CodeAST* block;
    int lineno;

    ~IfAST() {

    }

};

std::string IfAST::OutputCode() {
    return "if(" + expression->OutputCode() + ") {\n" + block->OutputCode() + "}";
}