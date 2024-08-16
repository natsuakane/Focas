#include "Lexer.h"
#include "Token.h"
#include "EOLToken.h"
#include "IdentifierToken.h"
#include "NumberToken.h"
#include "OperatorToken.h"
#include "AbstractSyntaxTree.h"
#include "CharAST.h"
#include "DeclarationAST.h"
#include "DivisionAST.h"
#include "FloatNumberAST.h"
#include "IdentifierAST.h"
#include "MinusAST.h"
#include "MultiplicationAST.h"
#include "NumberAST.h"
#include "PlusAST.h"
#include "Exceptions.h"

class Parser {
public:
    Parser(Lexer* lexer) {
        this->lexer = lexer;
    }



private:
    Lexer* lexer;

    bool isToken(std::string val) {
        return val == lexer->PeakToken(0)->GetValue();
    }

    AbstractSyntaxTree Factor();
    AbstractSyntaxTree PowerExpression();
    AbstractSyntaxTree MultiplicationExpression();
    AbstractSyntaxTree PlusExpression();
    AbstractSyntaxTree DeclarationExpression();

};

AbstractSyntaxTree