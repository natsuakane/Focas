#pragma once

#include "Token.h"
#include "TokenType.h"

class EOLToken : public Token {
    public:
        EOLToken(int lineno, std::string value) : Token(lineno, value) {
            this->lineno = lineno;
        }

        TokenType GetType() {
            return EOL;
        }

        std::string GetValue() {
            return "EOL";
        }

        int GetLineNo() {
            return lineno;
        }
    
    private:
        int lineno;

        ~EOLToken() {

        }
};