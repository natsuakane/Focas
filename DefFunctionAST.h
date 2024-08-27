#pragma once

#include <vector>
#include "AbstractSyntaxTree.h"
#include "Value.h"
#include "ArgmentAST.h"
#include "IdentifierAST.h"

class DefFunctionAST : public AbstractSyntaxTree {
public:
    DefFunctionAST(std::string returnType, IdentifierAST* identifier, std::vector<ArgmentAST> argments, AbstractSyntaxTree* tree, int lineno) {
        this->returnType = returnType; //型推論を実装
        this->argments.resize(argments.size());
        std::copy(argments.begin(), argments.end(), this->argments.begin());
        this->identifier = identifier;
        this->tree = tree;
        this->lineno = lineno;
    }

    AbstractSyntaxTree* GetChild(int i) {
        if(i == 0) return identifier;
        if(i == 1) return tree;

        throw std::runtime_error(TypeHasNoChildrenMoreThan("DefFunctionAST", 2, lineno));
    }

    std::string OutputCode();

private:
    std::string returnType;
    std::vector<ArgmentAST*> argments;
    IdentifierAST* identifier;
    AbstractSyntaxTree* tree;
    int lineno;

    ~DefFunctionAST() {

    }

};

std::string DefFunctionAST::OutputCode() {
    std::string code = returnType + " " + identifier->OutputCode() + "(";
    for(ArgmentAST* argment : argments) {
        code += argment->OutputCode() + ",";
    }
    code += ")" + tree->OutputCode();
    return code;
}