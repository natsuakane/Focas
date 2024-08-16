#pragma once

#include "AbstractSyntaxTree.h"
#include "Value.h"

class DivisionAST : public AbstractSyntaxTree {
public:
    DivisionAST(AbstractSyntaxTree* tree1, AbstractSyntaxTree* tree2, int lineno) {
        //最適化処理の時にintに変換
        this->tree1 = tree1;
        this->tree2 = tree2;
        this->lineno = lineno;
    }

    std::string OutputCode();

private:
    AbstractSyntaxTree* tree1;
    AbstractSyntaxTree* tree2;
    int lineno;

    ~DivisionAST() {

    }

};

std::string DivisionAST::OutputCode() {
    return "(" + tree1->OutputCode() + " / " + tree2->OutputCode() + ")";
}