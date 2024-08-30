#pragma once

#include <vector>
#include "AbstractSyntaxTree.h"
#include "Value.h"
#include "ArgmentAST.h"
#include "IdentifierAST.h"

class MakeObjectAST : public AbstractSyntaxTree {
public:
    MakeObjectAST(IdentifierAST* identifier, std::vector<AbstractSyntaxTree*> argments, int lineno) {
        this->argments.resize(argments.size());
        std::copy(argments.begin(), argments.end(), this->argments.begin());
        this->identifier = identifier;
        this->lineno = lineno;
    }

    AbstractSyntaxTree* GetChild(int i) {
        return argments[i];

        throw std::runtime_error(TypeHasNoChildrenMoreThan("MakeObjectAST", 1, lineno));
    }

    std::string OutputCode();

private:
    std::vector<AbstractSyntaxTree*> argments;
    IdentifierAST* identifier;
    int lineno;

    ~MakeObjectAST() {

    }

};

std::string MakeObjectAST::OutputCode() {
    std::string code = "new " + identifier->OutputCode() + "(";
    for(int i = 0; i < argments.size(); i++) {
        code += argments[i]->OutputCode() + ",";
    }
    code = code.substr(0, code.size() - 1);
    code += ")";

    return code;
}