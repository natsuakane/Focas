#pragma once

#include "AbstractSyntaxTree.h"
#include "Value.h"
#include "IdentifierAST.h"

class AssignmentAST : public AbstractSyntaxTree {
public:
    AssignmentAST(AbstractSyntaxTree* varName, AbstractSyntaxTree* tree, int lineno) {
        this->varName = varName;
        this->tree = tree;
        this->lineno = lineno;
    }

    AbstractSyntaxTree* GetChild(int i) {
        if(i == 0) return varName;
        if(i == 1) return tree;

        throw std::runtime_error(TypeHasNoChildrenMoreThan("AssignmentAST", 2, lineno));
    }

    std::string OutputCode();

private:
    AbstractSyntaxTree* varName;
    AbstractSyntaxTree* tree;
    int lineno;

    ~AssignmentAST() {

    }

};

std::string AssignmentAST::OutputCode() {
    return  "(" + varName->OutputCode() + " = " + tree->OutputCode() + ")";
}