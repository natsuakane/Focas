#pragma once

#include "AbstractSyntaxTree.h"
#include "Value.h"
#include "IdentifierAST.h"
#include "CodeAST.h"

class WhileAST : public AbstractSyntaxTree {
public:
    WhileAST(AbstractSyntaxTree* expression, CodeAST* block, int lineno) {
        this->expression = expression;
        this->block = block;
        this->lineno = lineno;
    }

    AbstractSyntaxTree* GetChild(int i) {
        if(i == 0) return expression;
        if(i == 1) return block;

        throw std::runtime_error(TypeHasNoChildrenMoreThan("WhileAST", 2, lineno));
    }

    std::string OutputCode();

private:
    AbstractSyntaxTree* expression;
    CodeAST* block;
    int lineno;

    ~WhileAST() {

    }

};

std::string WhileAST::OutputCode() {
    return "while(" + expression->OutputCode() + ") {\n" + block->OutputCode() + "}";
}