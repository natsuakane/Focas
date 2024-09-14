#pragma once

#include "AbstractSyntaxTree.h"
#include "Value.h"

class NegativeAST : public AbstractSyntaxTree {
public:
    NegativeAST(AbstractSyntaxTree* tree, int lineno) {
        this->tree = tree;
        this->lineno = lineno;
    }

    AbstractSyntaxTree* GetChild(int i) {
        if(i == 0) return tree;

        throw std::runtime_error(TypeHasNoChildrenMoreThan("NegativeAST", 1, lineno));
    }

    std::string OutputCode();

private:
    AbstractSyntaxTree* tree;
    int lineno;

    ~NegativeAST() {

    }

};

std::string NegativeAST::OutputCode() {
    return "(-" + tree->OutputCode() + ")";
}