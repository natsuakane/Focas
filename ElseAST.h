#pragma once

#include "AbstractSyntaxTree.h"
#include "Value.h"
#include "IdentifierAST.h"
#include "CodeAST.h"

class ElseAST : public AbstractSyntaxTree {
public:
    ElseAST(CodeAST* block, int lineno) {
        this->block = block;
        this->lineno = lineno;
    }

    AbstractSyntaxTree* GetChild(int i) {
        if(i == 0) return block;

        throw std::runtime_error(TypeHasNoChildrenMoreThan("ElseAST", 2, lineno));
    }

    std::string OutputCode();

private:
    CodeAST* block;
    int lineno;

    ~ElseAST() {

    }

};

std::string ElseAST::OutputCode() {
    return "else {\n" + block->OutputCode() + "}";
}