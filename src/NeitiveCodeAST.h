#pragma once

#include <vector>
#include "AbstractSyntaxTree.h"
#include "Value.h"

class NeitiveCodeAST : public AbstractSyntaxTree {
public:
    NeitiveCodeAST(std::string code, int lineno) {
        this->code = code;
        this->lineno = lineno;
    }

    AbstractSyntaxTree* GetChild(int i) {
        throw std::runtime_error(TypeHasNoChildren("NeitiveCodeAST", lineno));
    }

    std::string OutputCode();

private:
    std::string code;
    int lineno;

    ~NeitiveCodeAST() {

    }

};

std::string NeitiveCodeAST::OutputCode() {
    std::string result = code.substr(1, code.size() - 2);
    size_t pos = 0;
    while ((pos = result.find('$', pos)) != std::string::npos) {
        result.replace(pos, 1, "\"");
        pos += 1;
    }
    return result;
}