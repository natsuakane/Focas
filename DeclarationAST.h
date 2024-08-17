#pragma once

#include "AbstractSyntaxTree.h"
#include "Value.h"
#include "IdentifierAST.h"

class DeclarationAST : public AbstractSyntaxTree {
public:
    DeclarationAST(std::string type, IdentifierAST* identifier, AbstractSyntaxTree* tree, int lineno) {
        this->type = type;
        this->identifier = identifier;
        this->tree = tree;
        this->lineno = lineno;
    }

    std::string OutputCode();

private:
    std::string type;
    IdentifierAST* identifier;
    AbstractSyntaxTree* tree;
    int lineno;

    ~DeclarationAST() {

    }

};

std::string DeclarationAST::OutputCode() {
    return "const " + type + " " + identifier->OutputCode() + " = " + tree->OutputCode();
}