#pragma once

#include "AbstractSyntaxTree.h"
#include "Value.h"
#include "IdentifierAST.h"

class ArgmentAST : public AbstractSyntaxTree {
public:
    ArgmentAST(std::string type, IdentifierAST* identifier, int lineno) {
        this->type = type;
        this->identifier = identifier;
    }

    AbstractSyntaxTree* GetChild(int i) {
        throw std::runtime_error(TypeHasNoChildren("ArgmentAST", lineno));
    }

    std::string GetType() {
        return type;
    }

    std::string OutputCode();

    bool DoesNeedSemicolon() {
        return false;
    }

private:
    std::string type;
    IdentifierAST* identifier;
    int lineno;

    ~ArgmentAST() {

    }

};

std::string ArgmentAST::OutputCode() {
    return type + " " + identifier->OutputCode();
}