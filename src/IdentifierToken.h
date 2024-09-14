#pragma once

#include "Token.h"
#include "TokenType.h"

class IdentifierToken : public Token {
    public:
        IdentifierToken(int lineno, std::string value) : Token(lineno, value) {
            this->value = value;
            this->lineno = lineno;
        }

        TokenType GetType() {
            return Identifier;
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

        ~IdentifierToken() {

        }
};
