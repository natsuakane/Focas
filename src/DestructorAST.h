#pragma once

#include <vector>
#include "AbstractSyntaxTree.h"
#include "Value.h"
#include "ArgmentAST.h"
#include "IdentifierAST.h"

class DestructorAST : public AbstractSyntaxTree {
public:
    DestructorAST(IdentifierAST* identifier, AbstractSyntaxTree* tree, int lineno) {
        this->identifier = identifier;
        this->tree = tree;
        this->lineno = lineno;
    }

    AbstractSyntaxTree* GetChild(int i) {
        if(i == 0) return identifier;
        if(i == 1) return tree;

        throw std::runtime_error(TypeHasNoChildrenMoreThan("DestructorAST", 2, lineno));
    }

    std::string OutputCode();

private:
    IdentifierAST* identifier;
    AbstractSyntaxTree* tree;
    int lineno;

    ~DestructorAST() {

    }

};

std::string DestructorAST::OutputCode() {
    std::string code = "~" + identifier->OutputCode() + "()";
    code += " {\n" + tree->OutputCode() + "}";

    return code;
}