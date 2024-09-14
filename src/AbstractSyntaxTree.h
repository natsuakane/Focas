#pragma once

#include <string>
#include "Value.h"
#include "Exceptions.h"

class AbstractSyntaxTree {
public:
    virtual std::string OutputCode() = 0;
    virtual AbstractSyntaxTree* GetChild(int i) = 0;
    virtual ~AbstractSyntaxTree() {};

private:
};