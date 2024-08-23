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
#include "PowerAST.h"
#include "ModAST.h"
#include "CodeAST.h"
#include "Exceptions.h"

class Parser {
public:
    Parser(Lexer* lexer) {
        this->lexer = lexer;
    }

    AbstractSyntaxTree* GetTree();

private:
    Lexer* lexer;

    void IsExpectedTokne(std::string val) {
        Token* token = lexer->ReadToken();
        if(val != token->GetValue()) {
            throw std::runtime_error(UnexpectedToken(token->GetValue(), token->GetLineNo()));
        }
    }

    bool IsToken(std::string val) {
        return val == lexer->PeakToken(0)->GetValue();
    }
    
    int GetNowLineno() {
        return lexer->PeakToken(0)->GetLineNo();
    }

    AbstractSyntaxTree* Factor();
    AbstractSyntaxTree* PowerExpression();
    AbstractSyntaxTree* MultiplicationExpression();
    AbstractSyntaxTree* PlusExpression();
    AbstractSyntaxTree* DeclarationExpression();
    AbstractSyntaxTree* Code();

};

AbstractSyntaxTree* Parser::GetTree() {
    return Code();
}

AbstractSyntaxTree* Parser::Factor() {
    if(IsToken("(")) {
        AbstractSyntaxTree* result = DeclarationExpression();
        IsExpectedTokne(")");

        return result;
    }
    else if(lexer->PeakToken(0)->GetType() == Number) {
        if(lexer->PeakToken(0)->GetValue().find(".") != std::string::npos) {
            return new FloatNumberAST(std::stof(lexer->ReadToken()->GetValue()), GetNowLineno());
        }
        else {
            return new NumberAST(std::stoi(lexer->ReadToken()->GetValue()), GetNowLineno());
        }
    }
    else if(lexer->PeakToken(0)->GetType() == Identifier) {
        return new IdentifierAST(lexer->ReadToken()->GetValue(), GetNowLineno());
    }

    throw std::runtime_error(UnexpectedToken(lexer->PeakToken(0)->GetValue(), GetNowLineno()));
}

AbstractSyntaxTree* Parser::PowerExpression() {
    AbstractSyntaxTree* right = Factor();
    
    if(IsToken("**")) {
        IsExpectedTokne("**");
        AbstractSyntaxTree* left = PowerExpression();
        return new PowerAST(right, left, GetNowLineno());
    }

    return right;
}

AbstractSyntaxTree* Parser::MultiplicationExpression() {
    AbstractSyntaxTree* right = PowerExpression();

    if(IsToken("*")) {
        IsExpectedTokne("*");
        AbstractSyntaxTree* left = MultiplicationExpression();
        
        try {
            AbstractSyntaxTree* rightOfLeft = left->GetChild(0);
            AbstractSyntaxTree* leftOfLeft = left->GetChild(1);

            right = new MultiplicationAST(right, rightOfLeft, GetNowLineno());
            left = leftOfLeft;
        }
        catch(std::runtime_error error) {

        }

        return new MultiplicationAST(right, left, GetNowLineno());
    }
    else if(IsToken("/")) {
        IsExpectedTokne("/");
        AbstractSyntaxTree* left = MultiplicationExpression();

        try {
            AbstractSyntaxTree* rightOfLeft = left->GetChild(0);
            AbstractSyntaxTree* leftOfLeft = left->GetChild(1);

            right = new DivisionAST(right, rightOfLeft, GetNowLineno());
            left = leftOfLeft;
        }
        catch(std::runtime_error error) {

        }

        return new DivisionAST(right, left, GetNowLineno());
    }
    else if(IsToken("%")) {
        IsExpectedTokne("%");
        AbstractSyntaxTree* left = MultiplicationExpression();

        try {
            AbstractSyntaxTree* rightOfLeft = left->GetChild(0);
            AbstractSyntaxTree* leftOfLeft = left->GetChild(1);

            right = new ModAST(right, rightOfLeft, GetNowLineno());
            left = leftOfLeft;
        }
        catch(std::runtime_error) {

        }

        return new ModAST(right, left, GetNowLineno());
    }

    return right;
}

AbstractSyntaxTree* Parser::PlusExpression() {
    AbstractSyntaxTree* right = MultiplicationExpression();

    if(IsToken("+")) {
        IsExpectedTokne("+");
        AbstractSyntaxTree* left = PlusExpression();

        try {
            AbstractSyntaxTree* rightOfLeft = left->GetChild(0);
            AbstractSyntaxTree* leftOfLeft = left->GetChild(1);

            right = new PlusAST(right, rightOfLeft, GetNowLineno());
            left = leftOfLeft;
        }
        catch(std::runtime_error error) {

        }

        return new PlusAST(right, left, GetNowLineno());
    }
    else if(IsToken("-")) {
        IsExpectedTokne("-");
        AbstractSyntaxTree* left = MultiplicationExpression();

        try {
            AbstractSyntaxTree* rightOfLeft = left->GetChild(0);
            AbstractSyntaxTree* leftOfLeft = left->GetChild(1);

            right = new PlusAST(right, rightOfLeft, GetNowLineno());
            left = leftOfLeft;
        }
        catch(std::runtime_error error) {

        }

        return new MinusAST(right, left, GetNowLineno());
    }

    return right;
}

AbstractSyntaxTree* Parser::DeclarationExpression() {
    if(!IsToken("let")) {
        return PlusExpression();
    }

    IsExpectedTokne("let");

    std::string typeName;
    std::string varName = lexer->ReadToken()->GetValue();
    IdentifierAST* identifier = new IdentifierAST(varName, GetNowLineno());

    if(IsToken(":")){
        IsExpectedTokne(":");
        typeName = lexer->ReadToken()->GetValue();
    }

    IsExpectedTokne("=");
    AbstractSyntaxTree* value = PlusExpression();

    if(typeName == "") {
        typeName = "Error";
    }

    return new DeclarationAST(typeName, identifier, value, GetNowLineno());
}

AbstractSyntaxTree* Parser::Code() {
    std::vector<AbstractSyntaxTree*> expressions;
    while(!IsToken("EOF")) {
        expressions.push_back(DeclarationExpression());

        while(IsToken("EOL")) {
            IsExpectedTokne("EOL");
        }
    }

    return new CodeAST(expressions, GetNowLineno());
}