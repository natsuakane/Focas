#pragma once

#include "Token.h"
#include "TokenType.h"

class NumberToken : public Token {
    public:
        NumberToken(int lineno, std::string value) : Token(lineno, value) {
            this->value = value;
            this->lineno = lineno;
        }

        TokenType GetType() {
            return Number;
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

        ~NumberToken() {

        }
};