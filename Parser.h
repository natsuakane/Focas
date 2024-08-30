#include <typeinfo>
#include "Lexer.h"
#include "Token.h"
#include "EOLToken.h"
#include "IdentifierToken.h"
#include "NumberToken.h"
#include "OperatorToken.h"
#include "AbstractSyntaxTree.h"
#include "CharAST.h"
#include "ConstantAST.h"
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
#include "AssignmentAST.h"
#include "DefFunctionAST.h"
#include "CallFunctionAST.h"
#include "ArgmentAST.h"
#include "ClassAST.h"
#include "AccessModifier.h"
#include "Exceptions.h"

class Parser {
public:
    Parser(Lexer* lexer) {
        this->lexer = lexer;
    }

    AbstractSyntaxTree* GetTree();

private:
    Lexer* lexer;

    void IsExpectedToken(std::string val) {
        Token* token = lexer->ReadToken();
        if(val != token->GetValue()) {
            throw std::runtime_error(UnexpectedToken(token->GetValue(), token->GetLineNo()));
        }
    }

    bool IsToken(std::string val) {
        while(lexer->PeakToken(0)->GetValue() == "EOL") {
            IsExpectedToken("EOL");
        }
        return val == lexer->PeakToken(0)->GetValue();
    }
    
    int GetNowLineno() {
        return lexer->PeakToken(0)->GetLineNo();
    }

    AbstractSyntaxTree* Factor();
    AbstractSyntaxTree* PowerExpression();
    AbstractSyntaxTree* MultiplicationExpression();
    AbstractSyntaxTree* PlusExpression();
    AbstractSyntaxTree* AssignmentExpression();
    AbstractSyntaxTree* DeclarationExpression();
    AbstractSyntaxTree* ClassExpression();
    AbstractSyntaxTree* Code();

};

AbstractSyntaxTree* Parser::GetTree() {
    return Code();
}

AbstractSyntaxTree* Parser::Factor() {
    if(IsToken("(")) {
        IsExpectedToken("(");
        AbstractSyntaxTree* result = DeclarationExpression();
        IsExpectedToken(")");

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
        if(lexer->PeakToken(1)->GetValue() == "(") {
            std::string name = lexer->ReadToken()->GetValue();
            IdentifierAST* identifier = new IdentifierAST(name, GetNowLineno());
            std::vector<AbstractSyntaxTree*> argments;

            IsExpectedToken("(");
            while(true) {
                argments.push_back(AssignmentExpression());
                
                if(lexer->PeakToken(0)->GetValue() == ")") {
                    break;
                }

                IsExpectedToken(",");
            }
            IsExpectedToken(")");

            return new CallFunctionAST(identifier, argments, GetNowLineno());
        }
        return new IdentifierAST(lexer->ReadToken()->GetValue(), GetNowLineno());
    }
    else if(lexer->PeakToken(0)->GetType() == String) {
        return new StringAST(lexer->ReadToken()->GetValue(), GetNowLineno());
    }

    throw std::runtime_error(UnexpectedToken(lexer->PeakToken(0)->GetValue(), GetNowLineno()));
}

AbstractSyntaxTree* Parser::PowerExpression() {
    AbstractSyntaxTree* right = Factor();
    
    if(IsToken("**")) {
        IsExpectedToken("**");
        AbstractSyntaxTree* left = PowerExpression();
        return new PowerAST(right, left, GetNowLineno());
    }

    return right;
}

AbstractSyntaxTree* Parser::MultiplicationExpression() {
    AbstractSyntaxTree* right = PowerExpression();

    if(IsToken("*")) {
        IsExpectedToken("*");
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
        IsExpectedToken("/");
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
        IsExpectedToken("%");
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
        IsExpectedToken("+");
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
        IsExpectedToken("-");
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

AbstractSyntaxTree* Parser::AssignmentExpression() {
    AbstractSyntaxTree* right = PlusExpression();

    if(IsToken("=")) {
        IsExpectedToken("=");

        AbstractSyntaxTree* left = AssignmentExpression();

        return new AssignmentAST(right, left, GetNowLineno());
    }

    return right;
}

AbstractSyntaxTree* Parser::DeclarationExpression() {
    if(IsToken("let")) {
        IsExpectedToken("let");

        std::string typeName;
        std::string varName = lexer->ReadToken()->GetValue();
        IdentifierAST* identifier = new IdentifierAST(varName, GetNowLineno());

        IsExpectedToken(":");
        typeName = lexer->ReadToken()->GetValue();

        IsExpectedToken("=");
        AbstractSyntaxTree* value = PlusExpression();

        return new DeclarationAST(typeName, identifier, value, GetNowLineno());
    }
    else if(IsToken("const")) {
        IsExpectedToken("const");

        std::string typeName;
        std::string varName = lexer->ReadToken()->GetValue();
        IdentifierAST* identifier = new IdentifierAST(varName, GetNowLineno());

            IsExpectedToken(":");
            typeName = lexer->ReadToken()->GetValue();

        IsExpectedToken("=");
        AbstractSyntaxTree* value = PlusExpression();

        return new ConstantAST(typeName, identifier, value, GetNowLineno());
    }
    else if(IsToken("func")) {
        IsExpectedToken("func");

        std::string returnTypeName;
        std::string funcName = lexer->ReadToken()->GetValue();
        IdentifierAST* identifier = new IdentifierAST(funcName, GetNowLineno());
        std::vector<ArgmentAST*> argments;
        std::vector<AbstractSyntaxTree*> body;
        CodeAST* code;

        IsExpectedToken("(");
        while(true) {
            std::string argmentName = lexer->ReadToken()->GetValue();
            IsExpectedToken(":");
            std::string argmentType = lexer->ReadToken()->GetValue();

            IdentifierAST* identifier = new IdentifierAST(argmentName, GetNowLineno());
            argments.push_back(new ArgmentAST(argmentType, identifier, GetNowLineno()));

            if(IsToken(")")) {
                break;
            }

            IsExpectedToken(",");
        }
        IsExpectedToken(")");

        IsExpectedToken(":");
        returnTypeName = lexer->ReadToken()->GetValue();

        IsExpectedToken("=>");

        while(!IsToken("end")) {
            body.push_back(DeclarationExpression());
        }
        IsExpectedToken("end");

        code = new CodeAST(body, GetNowLineno());

        return new DefFunctionAST(returnTypeName, identifier, argments, code, GetNowLineno());
    }

    return AssignmentExpression();
}

AbstractSyntaxTree* Parser::ClassExpression() {
    if(IsToken("class")) {
        IsExpectedToken("class");

        std::string name = lexer->ReadToken()->GetValue();
        IdentifierAST* identifier = new IdentifierAST(name, GetNowLineno());
        std::vector<AbstractSyntaxTree*> members;
        std::vector<AccessModifier> membersAccessModifiers;

        IsExpectedToken("=>");

        while(!IsToken("end")) {
            if(IsToken("public")) {
                IsExpectedToken("public");
                membersAccessModifiers.push_back(AccessModifier(PUBLIC));
            }
            else if(IsToken("private")) {
                IsExpectedToken("private");
                membersAccessModifiers.push_back(AccessModifier(PRIVATE));
            }
            else if(IsToken("protected")) {
                IsExpectedToken("protected");
                membersAccessModifiers.push_back(AccessModifier(PROTECTED));
            }
            else {
                membersAccessModifiers.push_back(AccessModifier(PRIVATE));
            }

            members.push_back(DeclarationExpression());
        }
        IsExpectedToken("end");

        return new ClassAST(identifier, members, membersAccessModifiers, GetNowLineno());
    }

    return DeclarationExpression();
}

AbstractSyntaxTree* Parser::Code() {
    std::vector<AbstractSyntaxTree*> expressions;
    while(!IsToken("EOF")) {
        expressions.push_back(ClassExpression());
    }

    return new CodeAST(expressions, GetNowLineno());
}