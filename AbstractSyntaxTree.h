#pragma once

#include <string>
#include "Value.h"

class AbstractSyntaxTree {
public:
    virtual std::string OutputCode() = 0;
    virtual ~AbstractSyntaxTree() {};

private:
};