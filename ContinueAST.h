#pragma once

#include <vector>
#include "AbstractSyntaxTree.h"
#include "Value.h"

class ContinueAST : public AbstractSyntaxTree {
public:
    ContinueAST(int lineno) {
        this->lineno = lineno;
    }

    AbstractSyntaxTree* GetChild(int i) {
        throw std::runtime_error(TypeHasNoChildren("ContinueAST", lineno));
    }

    std::string OutputCode();

private:
    int lineno;

    ~ContinueAST() {

    }

};

std::string ContinueAST::OutputCode() {
    return "continue";
}