#pragma once

#include "AbstractSyntaxTree.h"
#include "Value.h"

class MoreThanOrEqualAST : public AbstractSyntaxTree {
public:
    MoreThanOrEqualAST(AbstractSyntaxTree* tree1, AbstractSyntaxTree* tree2, int lineno) {
        this->tree1 = tree1;
        this->tree2 = tree2;
        this->lineno = lineno;
    }

    AbstractSyntaxTree* GetChild(int i) {
        if(i == 0) return tree1;
        if(i == 1) return tree2;

        throw std::runtime_error(TypeHasNoChildrenMoreThan("MoreThanOrEqualAST", 2, lineno));
    }

    std::string OutputCode();

private:
    AbstractSyntaxTree* tree1;
    AbstractSyntaxTree* tree2;
    int lineno;

    ~MoreThanOrEqualAST() {

    }

};

std::string MoreThanOrEqualAST::OutputCode() {
    return "(" + tree1->OutputCode() + " >= " + tree2->OutputCode() + ")";
}