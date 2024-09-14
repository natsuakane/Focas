#pragma once

#include "Token.h"
#include "TokenType.h"

class EOFToken : public Token {
    public:
        EOFToken(int lineno, std::string value) : Token(lineno, value) {
            this->lineno = lineno;
        }

        TokenType GetType() {
            return EndOfFile;
        }

        std::string GetValue() {
            return "EOF";
        }

        int GetLineNo() {
            return lineno;
        }
    
    private:
        int lineno;

        ~EOFToken() {

        }
};