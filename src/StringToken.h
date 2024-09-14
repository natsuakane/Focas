#pragma once

#include "Token.h"
#include "TokenType.h"

class StringToken : public Token {
    public:
        StringToken(int lineno, std::string value) : Token(lineno, value) {
            this->value = value;
            this->lineno = lineno;
        }

        TokenType GetType() {
            return String;
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

        ~StringToken() {

        }
};
