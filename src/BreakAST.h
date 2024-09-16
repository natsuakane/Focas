#pragma once

#include <vector>
#include "AbstractSyntaxTree.h"
#include "Value.h"

class BreakAST : public AbstractSyntaxTree {
public:
    BreakAST(int lineno) {
        this->lineno = lineno;
    }

    AbstractSyntaxTree* GetChild(int i) {
        throw std::runtime_error(TypeHasNoChildren("BreakAST", lineno));
    }

    std::string OutputCode();

    bool DoesNeedSemicolon() {
        return true;
    }

private:
    int lineno;

    ~BreakAST() {

    }

};

std::string BreakAST::OutputCode() {
    return "break";
}