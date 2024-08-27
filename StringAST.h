#pragma once

#include <string>
#include "AbstractSyntaxTree.h"
#include "Value.h"

class StringAST : public AbstractSyntaxTree {
public:
    StringAST(std::string v, int lineno) {
        this->value = new Value(v, lineno);
        this->lineno = lineno;
    }

    AbstractSyntaxTree* GetChild(int i) {
        throw std::runtime_error(TypeHasNoChildren("String", lineno));
    }

    ~StringAST() {
        delete value;
    }

    std::string OutputCode();

private:
    Value* value;
    int lineno;

};

std::string StringAST::OutputCode() {
    return "\"" + value->GetStr() + "\"";
}