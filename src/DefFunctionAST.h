#pragma once

#include <vector>
#include "AbstractSyntaxTree.h"
#include "Value.h"
#include "ArgmentAST.h"
#include "IdentifierAST.h"

class DefFunctionAST : public AbstractSyntaxTree {
public:
    DefFunctionAST(std::string returnType, IdentifierAST* identifier, std::vector<ArgmentAST*> argments, AbstractSyntaxTree* tree, int lineno) {
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

    bool DoesNeedSemicolon() {
        return false;
    }

};

std::string DefFunctionAST::OutputCode() {
    std::string code = returnType + " " + identifier->OutputCode() + "(";

    if(argments.size() != 0) {
        for(int i = 0; i < argments.size(); i++) {
            code += argments[i]->OutputCode() + ",";
        }
        code = code.substr(0, code.size() - 1);
    }
    
    code += ") {\n" + tree->OutputCode() + "}";

    return code;
}