#pragma once

#include <vector>
#include "AbstractSyntaxTree.h"
#include "Value.h"
#include "ArgmentAST.h"
#include "IdentifierAST.h"

class VirtualDestructorAST : public AbstractSyntaxTree {
public:
    VirtualDestructorAST(IdentifierAST* identifier, int lineno) {
        this->identifier = identifier;
        this->lineno = lineno;
    }

    AbstractSyntaxTree* GetChild(int i) {
        if(i == 0) return identifier;

        throw std::runtime_error(TypeHasNoChildrenMoreThan("VirtualDestructorAST", 1, lineno));
    }

    std::string OutputCode();

    bool DoesNeedSemicolon() {
        return false;
    }

private:
    IdentifierAST* identifier;
    int lineno;

    ~VirtualDestructorAST() {

    }

};

std::string VirtualDestructorAST::OutputCode() {
    std::string code = "virtual ~" + identifier->OutputCode() + "() {}";

    return code;
}