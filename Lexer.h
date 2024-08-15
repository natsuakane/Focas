#include <vector>
#include <queue>
#include <string>
#include <regex>
#include "Token.h"
#include "IdentifierToken.h"
#include "NumberToken.h"
#include "OperatorToken.h"
#include "EOLToken.h"
#include "TokenType.h"
#include "Exceptions.h"

class Lexer {
    public:
        Lexer(std::string input) {
            code = input;
            codePointerInLine = 0;
            lineno = 0;

            identifierRegex = std::regex("^[a-zA-Z_][a-zA-Z0-9_]*$");
            numberRegex = std::regex("^(\\-|\\+)?(0x|0b|0o)?[0-9]+(\\.[0-9]*)?$");
            operatorRegex = std::regex("^\\+|\\-|\\*|/|%|\\(|\\)$");
        }

        Token* ReadToken();
        Token* PeakToken(int n);

    private:
        std::string code;
        int codePointerInLine;
        int lineno;
        std::deque<Token*> queue;

        std::regex identifierRegex;
        std::regex numberRegex;
        std::regex operatorRegex;

        void ReadLineToQueue();
        Token* GetNextToken();

};

Token* Lexer::ReadToken() {
    if(queue.size() == 0) {
        ReadLineToQueue();
    }

    Token* token = queue.front();
    queue.pop_front();

    return token;
}

void Lexer::ReadLineToQueue() {
    Token* token = GetNextToken();

    while(token->GetType() != EOL) {
        queue.push_back(token);
        token = GetNextToken();
    }

    queue.push_back(new EOLToken(lineno, ""));
}

Token* Lexer::GetNextToken() {
    while(code[codePointerInLine] == ' ' || code[codePointerInLine] == '\t') {
        codePointerInLine++;
    }

    if(code[codePointerInLine] == '\n') {
        lineno++;
        codePointerInLine++;

        return new EOLToken(lineno-1, "");
    }
    else if(std::regex_match(code.substr(codePointerInLine, 1), identifierRegex)) {
        int tokenLength = 1;
        while(std::regex_match(code.substr(codePointerInLine, tokenLength), identifierRegex)) {
            tokenLength++;
        }
        tokenLength--;

        int codePointer = codePointerInLine;
        codePointerInLine += tokenLength;
        return new IdentifierToken(lineno, code.substr(codePointer, tokenLength));
    }
    else if(std::regex_match(code.substr(codePointerInLine, 1), operatorRegex)) {
        int tokenLength = 1;
        while(std::regex_match(code.substr(codePointerInLine, tokenLength), operatorRegex)) {
            tokenLength++;
        }
        tokenLength--;

        int codePointer = codePointerInLine;
        codePointerInLine += tokenLength;
        return new OperatorToken(lineno, code.substr(codePointer, tokenLength));
    }
    else if(std::regex_match(code.substr(codePointerInLine, 1), numberRegex)) {
        int tokenLength = 1;
        while(std::regex_match(code.substr(codePointerInLine, tokenLength), numberRegex)) {
            tokenLength++;
        }
        tokenLength--;
        
        int codePointer = codePointerInLine;
        codePointerInLine += tokenLength;
        return new NumberToken(lineno, code.substr(codePointer, tokenLength));
    }

    throw std::runtime_error(ExpectedCharacter(code[codePointerInLine], lineno, codePointerInLine));
}