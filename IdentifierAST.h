#pragma once

#include "AbstractSyntaxTree.h"
#include "Value.h"

class IdentifierAST : public AbstractSyntaxTree {
public:
    IdentifierAST(std::string name, int lineno) {
        this->name = name;
        this->lineno = lineno;
    }

    std::string OutputCode();

private:
    std::string name;
    int lineno;

    ~IdentifierAST() {

    }

};

std::string IdentifierAST::OutputCode() {
    return name;
}