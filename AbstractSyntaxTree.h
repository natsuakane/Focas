#pragma once

#include "Value.h"

class AbstractSyntaxTree {
public:
    virtual Value* Execute() = 0;
    virtual ~AbstractSyntaxTree() {};

private:
};