#pragma once

#include "AbstractSyntaxTree.h"
#include "Value.h"

class PowerAST : public AbstractSyntaxTree {
public:
    PowerAST(AbstractSyntaxTree* tree1, AbstractSyntaxTree* tree2, int lineno) {
        this->tree1 = tree1;
        this->tree2 = tree2;
        this->lineno = lineno;
    }

    std::string OutputCode();

private:
    AbstractSyntaxTree* tree1;
    AbstractSyntaxTree* tree2;
    int lineno;

    ~PowerAST() {

    }

};

std::string PowerAST::OutputCode() {
    return "pow(" + tree1->OutputCode() + ", " + tree2->OutputCode() + ")";
}