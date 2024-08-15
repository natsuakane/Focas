#pragma once

#include "Token.h"
#include "TokenType.h"

class OperatorToken : public Token {
    public:
        OperatorToken(int lineno, std::string value) : Token(lineno, value) {
            this->value = value;
            this->lineno = lineno;
        }

        TokenType GetType() {
            return Operator;
        }

        std::string GetValue() {
            return value;
        }

        int GetLineNo() {
            return lineno;
        }
    
    private:
        std::string value;
        int lineno;

        ~OperatorToken() {

        }
};