#pragma once

#include "AbstractSyntaxTree.h"
#include "Value.h"

class IdentifierAST : public AbstractSyntaxTree {
public:
    IdentifierAST(std::string name, int lineno) {
        this->name = name;
        this->lineno = lineno;
    }

    AbstractSyntaxTree* GetChild(int i) {
        throw std::runtime_error(TypeHasNoChildren("Identifier", lineno));
    }

    std::string OutputCode();

    bool DoesNeedSemicolon() {
        return true;
    }

private:
    std::string name;
    int lineno;

    ~IdentifierAST() {

    }

};

std::string IdentifierAST::OutputCode() {
    return name;
}