#pragma once

#include <string>
#include "TokenType.h"

class Token {
public:
    Token(int lineno, std::string str) : lineno(lineno), str(str) {};
    virtual TokenType GetType() = 0;
    virtual std::string GetValue() = 0;
    virtual int GetLineNo() = 0;
    virtual ~Token() {};

private:
    int lineno;
    std::string str;
};