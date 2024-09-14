#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "AbstractSyntaxTree.h"
#include "Value.h"

class CodeAST : public AbstractSyntaxTree {
public:
    CodeAST(std::vector<AbstractSyntaxTree*> expressions, int lineno) {
        this->expressions = expressions;
        this->lineno = lineno;
    }

    AbstractSyntaxTree* GetChild(int i) {
        return expressions[i];
    }

    std::string OutputCode();

private:
    std::vector<AbstractSyntaxTree *> expressions;
    int lineno;

    ~CodeAST() {

    }

};

std::string CodeAST::OutputCode() {
    std::string result = "";
    for(int i = 0; i < expressions.size(); i++) {
        result += expressions[i]->OutputCode();
        result += ";\n";
    }

    return result;
}