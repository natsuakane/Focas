#pragma once

#include <vector>
#include "AbstractSyntaxTree.h"
#include "Value.h"

class ReturnAST : public AbstractSyntaxTree {
public:
    ReturnAST(AbstractSyntaxTree* value, int lineno) {
        this->value = value;
        this->lineno = lineno;
    }

    AbstractSyntaxTree* GetChild(int i) {
        if(i == 0) return value;

        throw std::runtime_error(TypeHasNoChildren("ReturnAST", lineno));
    }

    std::string OutputCode();

    bool DoesNeedSemicolon() {
        return true;
    }

private:
    AbstractSyntaxTree* value;
    int lineno;

    ~ReturnAST() {

    }

};

std::string ReturnAST::OutputCode() {
    return "return " + value->OutputCode();
}