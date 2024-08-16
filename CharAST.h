#pragma once

#include "AbstractSyntaxTree.h"
#include "Value.h"

class CharAST : public AbstractSyntaxTree {
public:
    CharAST(char v, int lineno) {
        this->value = new Value(v, lineno);
        this->lineno = lineno;
    }

    std::string OutputCode();

private:
    Value* value;
    int lineno;

    ~CharAST() {

    }

};

std::string CharAST::OutputCode() {
    return "\'" + std::to_string(value->GetChar()) + "\'";
}