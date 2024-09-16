#pragma once

#include "AbstractSyntaxTree.h"
#include "Value.h"
#include "IdentifierAST.h"
#include "CodeAST.h"

class ForAST : public AbstractSyntaxTree {
public:
    ForAST(AbstractSyntaxTree* expression1, AbstractSyntaxTree* expression2, AbstractSyntaxTree* expression3, CodeAST* block, int lineno) {
        this->expression1 = expression1;
        this->expression2 = expression2;
        this->expression3 = expression3;
        this->block = block;
        this->lineno = lineno;
    }

    AbstractSyntaxTree* GetChild(int i) {
        if(i == 0) return expression1;
        if(i == 1) return expression2;
        if(i == 2) return expression3;
        if(i == 3) return block;

        throw std::runtime_error(TypeHasNoChildrenMoreThan("ForAST", 2, lineno));
    }

    std::string OutputCode();

    bool DoesNeedSemicolon() {
        return false;
    }

private:
    AbstractSyntaxTree* expression1;
    AbstractSyntaxTree* expression2;
    AbstractSyntaxTree* expression3;
    CodeAST* block;
    int lineno;

    ~ForAST() {

    }

};

std::string ForAST::OutputCode() {
    return "for(" + expression1->OutputCode() + ";"
             + expression2->OutputCode() + ";"
             + expression3->OutputCode() + ") {\n" + block->OutputCode() + "}";
}