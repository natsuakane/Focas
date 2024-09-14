#pragma once

#include "AbstractSyntaxTree.h"
#include "Value.h"
#include "IdentifierAST.h"

class ConstantAST : public AbstractSyntaxTree {
public:
    ConstantAST(std::string type, IdentifierAST* identifier, AbstractSyntaxTree* tree, int lineno) {
        this->type = type; //型推論を実装
        this->identifier = identifier;
        this->tree = tree;
        this->lineno = lineno;
    }

    AbstractSyntaxTree* GetChild(int i) {
        if(i == 0) return identifier;
        if(i == 1) return tree;

        throw std::runtime_error(TypeHasNoChildrenMoreThan("ConstantAST", 2, lineno));
    }

    std::string OutputCode();

private:
    std::string type;
    IdentifierAST* identifier;
    AbstractSyntaxTree* tree;
    int lineno;

    ~ConstantAST() {

    }

};

std::string ConstantAST::OutputCode() {
    return "const " + type + " " + identifier->OutputCode() + " = " + tree->OutputCode();
}