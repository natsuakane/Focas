#pragma once

#include "AbstractSyntaxTree.h"
#include "Value.h"
#include "IdentifierAST.h"

class DeclarationAST : public AbstractSyntaxTree {
public:
    DeclarationAST(std::string type, IdentifierAST* identifier, AbstractSyntaxTree* tree, int lineno) {
        this->type = type; //型推論を実装
        this->identifier = identifier;
        this->tree = tree;
        this->lineno = lineno;
    }

    AbstractSyntaxTree* GetChild(int i) {
        if(i == 0) return identifier;
        if(i == 1) return tree;

        throw std::runtime_error(TypeHasNoChildrenMoreThan("DeclarationAST", 2, lineno));
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
    return type + " " + identifier->OutputCode() + " = " + tree->OutputCode();
}