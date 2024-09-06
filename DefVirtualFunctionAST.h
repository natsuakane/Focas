#pragma once

#include <vector>
#include "AbstractSyntaxTree.h"
#include "Value.h"
#include "ArgmentAST.h"
#include "IdentifierAST.h"

class DefVirtualFunctionAST : public AbstractSyntaxTree {
public:
    DefVirtualFunctionAST(std::string returnType, IdentifierAST* identifier, std::vector<ArgmentAST*> argments, int lineno) {
        this->returnType = returnType; //型推論を実装
        this->argments.resize(argments.size());
        std::copy(argments.begin(), argments.end(), this->argments.begin());
        this->identifier = identifier;
        this->lineno = lineno;
    }

    AbstractSyntaxTree* GetChild(int i) {
        if(i == 0) return identifier;

        throw std::runtime_error(TypeHasNoChildrenMoreThan("DefVirtualFunctionAST", 1, lineno));
    }

    std::string OutputCode();

private:
    std::string returnType;
    std::vector<ArgmentAST*> argments;
    IdentifierAST* identifier;
    int lineno;

    ~DefVirtualFunctionAST() {

    }

};

std::string DefVirtualFunctionAST::OutputCode() {
    std::string code = "virtual " + returnType + " " + identifier->OutputCode() + "(";

    if(argments.size() != 0) {
        for(int i = 0; i < argments.size(); i++) {
            code += argments[i]->OutputCode() + ",";
        }
        code = code.substr(0, code.size() - 1);
    }
    
    code += ") = 0;";

    return code;
}