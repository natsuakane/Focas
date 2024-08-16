#pragma once

#include "AbstractSyntaxTree.h"
#include "Value.h"
#include "IdentifierAST.h"

class DeclarationAST : public AbstractSyntaxTree {
public:
    DeclarationAST(IdentifierAST* identifier, AbstractSyntaxTree* tree, int lineno) {
        this->identifier = identifier;
        this->tree = tree;
        this->lineno = lineno;
    }

    std::string OutputCode();

private:
    IdentifierAST* identifier;
    AbstractSyntaxTree* tree;
    int lineno;

    ~DeclarationAST() {

    }

};

std::string DeclarationAST::OutputCode() {
    return "const var " + identifier->OutputCode() + " = " + tree->OutputCode();
}