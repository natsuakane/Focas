#pragma once

#include <vector>
#include "AbstractSyntaxTree.h"
#include "Value.h"

class IncludeAST : public AbstractSyntaxTree {
public:
    IncludeAST(AbstractSyntaxTree* fileName, bool isHeader, int lineno) {
        this->fileName = fileName;
        this->isHeader = isHeader;
        this->lineno = lineno;
    }

    AbstractSyntaxTree* GetChild(int i) {
        if(i == 0) return fileName;

        throw std::runtime_error(TypeHasNoChildren("IncludeAST", lineno));
    }

    std::string OutputCode();

    ~IncludeAST() {

    }

private:
    AbstractSyntaxTree* fileName;
    bool isHeader;
    int lineno;

};

std::string IncludeAST::OutputCode() {
    return "#include \"" + fileName->OutputCode() + (isHeader ? ".h\"" : ".cpp\"");
}