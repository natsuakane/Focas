#pragma once

#include <vector>
#include "AbstractSyntaxTree.h"
#include "Value.h"

class IncludeAST : public AbstractSyntaxTree {
public:
    IncludeAST(AbstractSyntaxTree* fileName, int lineno) {
        this->fileName = fileName;
        this->lineno = lineno;
    }

    AbstractSyntaxTree* GetChild(int i) {
        if(i == 0) return fileName;

        throw std::runtime_error(TypeHasNoChildren("IncludeAST", lineno));
    }

    std::string OutputCode();

private:
    AbstractSyntaxTree* fileName;
    int lineno;

    ~IncludeAST() {

    }

};

std::string IncludeAST::OutputCode() {
    return "#include \"" + fileName->OutputCode() + ".cpp\"";
}