#pragma once

#include <vector>
#include "AbstractSyntaxTree.h"
#include "Value.h"

class IncludeAST : public AbstractSyntaxTree {
public:
    IncludeAST(AbstractSyntaxTree* fileName, bool isHeader, bool isStandard, int lineno) {
        this->fileName = fileName;
        this->isHeader = isHeader;
        this->isStandard = isStandard;
        this->lineno = lineno;
    }

    AbstractSyntaxTree* GetChild(int i) {
        if(i == 0) return fileName;

        throw std::runtime_error(TypeHasNoChildren("IncludeAST", lineno));
    }

    std::string OutputCode();

    bool DoesNeedSemicolon() {
        return false;
    }

    ~IncludeAST() {

    }

private:
    AbstractSyntaxTree* fileName;
    bool isHeader;
    bool isStandard;
    int lineno;

};

std::string IncludeAST::OutputCode() {
    if(!isStandard) {
        return "#include \"" + fileName->OutputCode() + (isHeader ? ".h\"" : ".cpp\"");
    }

    return "#include <" + fileName->OutputCode() + ">";
}