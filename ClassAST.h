#pragma once

#include <vector>
#include "AbstractSyntaxTree.h"
#include "Value.h"
#include "IdentifierAST.h"
#include "AccessModifier.h"

class ClassAST : public AbstractSyntaxTree {
public:
    ClassAST(IdentifierAST* identifier, std::vector<std::string> inheritances, std::vector<AbstractSyntaxTree*> members, std::vector<AccessModifier> membersAccessModifiers, int lineno) {
        this->members.resize(members.size());
        std::copy(members.begin(), members.end(), this->members.begin());
        this->membersAccessModifiers.resize(membersAccessModifiers.size());
        std::copy(membersAccessModifiers.begin(), membersAccessModifiers.end(), this->membersAccessModifiers.begin());
        this->identifier = identifier;
        this->inheritances.resize(inheritances.size());
        std::copy(inheritances.begin(), inheritances.end(), this->inheritances.begin());
        this->lineno = lineno;
    }

    AbstractSyntaxTree* GetChild(int i) {
        return members[i];

        throw std::runtime_error(TypeHasNoChildrenMoreThan("ClassAST", 1, lineno));
    }

    std::string OutputCode();

private:
    std::vector<AbstractSyntaxTree*> members;
    std::vector<AccessModifier> membersAccessModifiers;
    IdentifierAST* identifier;
    std::vector<std::string> inheritances;
    int lineno;

    ~ClassAST() {

    }

};

std::string ClassAST::OutputCode() {
    std::string code = "class " + identifier->OutputCode();
    
    if(inheritances.size() != 0) {
        code += " : ";
        for(int i = 0; i < inheritances.size(); i ++) {
            if(i != 0) code += ", ";
            code += inheritances[i];
        }
    }

    code += " {\npublic:\n";
    for(int i = 0; i < members.size(); i++) {
        if(membersAccessModifiers[i] == PUBLIC) {
            code += members[i]->OutputCode() + ";\n";
        }
    }

    code += "private:\n";
    for(int i = 0; i < members.size(); i++) {
        if(membersAccessModifiers[i] == PRIVATE) {
            code += members[i]->OutputCode() + ";\n";
        }
    }

    code += "protected:\n";
    for(int i = 0; i < members.size(); i++) {
        if(membersAccessModifiers[i] == PROTECTED) {
            code += members[i]->OutputCode() + ";\n";
        }
    }
    
    code += "}";

    return code;
}