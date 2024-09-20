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
#include "DefVirtualFunctionAST.h"
#include "CallFunctionAST.h"
#include "ArgmentAST.h"
#include "InterfaceAST.h"
#include "ClassAST.h"
#include "AccessModifier.h"
#include "MakeObjectAST.h"
#include "ConstructorAST.h"
#include "DestructorAST.h"
#include "VirtualDestructorAST.h"
#include "NegativeAST.h"
#include "IfAST.h"
#include "ForAST.h"
#include "WhileAST.h"
#include "ElifAST.h"
#include "ElseAST.h"
#include "EqualAST.h"
#include "NotEqualAST.h"
#include "MoreThanAST.h"
#include "LessThanAST.h"
#include "MoreThanOrEqualAST.h"
#include "LessThanOrEqualAST.h"
#include "AndAST.h"
#include "OrAST.h"
#include "DotAST.h"
#include "BreakAST.h"
#include "ReturnAST.h"
#include "ContinueAST.h"
#include "IncludeAST.h"
#include "NeitiveCodeAST.h"
#include "Exceptions.h"

class Parser {
public:
    Parser(Lexer* lexer) {
        this->lexer = lexer;
    }

    AbstractSyntaxTree* GetTree();

private:
    Lexer* lexer;
    std::vector<IncludeAST> initialIncludes;

    void AdvanceToken(std::string val) {
        while(lexer->PeakToken(0)->GetValue() == "EOL") {
            lexer->ReadToken();
        }

        Token* token = lexer->ReadToken();
        if(val != token->GetValue()) {
            throw std::runtime_error(UnexpectedToken(token->GetValue(), token->GetLineNo()));
        }
    }

    bool IsToken(std::string val) {
        while(lexer->PeakToken(0)->GetValue() == "EOL") {
            lexer->ReadToken();
        }
        return val == lexer->PeakToken(0)->GetValue();
    }
    
    int GetNowLineno() {
        return lexer->PeakToken(0)->GetLineNo();
    }

    std::string GetTypeName() {
        std::string type = lexer->ReadToken()->GetValue();
        if(type == "ref") {
            return lexer->ReadToken()->GetValue() + "*";
        }

        return type;
    }

    std::string GetVarName() {
        std::string name = lexer->ReadToken()->GetValue();
        if(name == "ref") {
            return "(*" + lexer->ReadToken()->GetValue() + ")";
        }
        if(name == "add") {
            return "(&" + lexer->ReadToken()->GetValue() + ")";
        }

        return name;
    }

    void AddToInitialIncludes(IncludeAST include) {
        initialIncludes.push_back(include);
    }

    std::string GetInitialIncludesAsString() {
        std::string code = "";
        for(int i = 0; i < initialIncludes.size(); i++) {
            code += initialIncludes[i].OutputCode() = "\n";
        }

        return code;
    }

    CodeAST* GetBlock() {
        std::vector<AbstractSyntaxTree*> statements;

        AdvanceToken("=>");
        while(!IsToken("end")) {
            statements.push_back(OtherStatements());
        }
        AdvanceToken("end");

        return new CodeAST(statements, GetNowLineno());
    }

    AbstractSyntaxTree* Factor();
    AbstractSyntaxTree* DotExpression();
    AbstractSyntaxTree* UnuOpExp();
    AbstractSyntaxTree* PowerExpression();
    AbstractSyntaxTree* MultiplicationExpression();
    AbstractSyntaxTree* PlusExpression();
    AbstractSyntaxTree* CompareExpression();
    AbstractSyntaxTree* LogicalAndExpression();
    AbstractSyntaxTree* LogicalOrExpression();
    AbstractSyntaxTree* AssignmentExpression();
    AbstractSyntaxTree* DeclarationStatement();
    AbstractSyntaxTree* ClassStatement();
    AbstractSyntaxTree* OtherStatements();
    AbstractSyntaxTree* Code();

};

AbstractSyntaxTree* Parser::GetTree() {
    return Code();
}

AbstractSyntaxTree* Parser::Factor() {
    if(IsToken("(")) {
        AdvanceToken("(");
        AbstractSyntaxTree* result = DeclarationStatement();
        AdvanceToken(")");

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
            std::string name = GetVarName();
            IdentifierAST* identifier = new IdentifierAST(name, GetNowLineno());
            std::vector<AbstractSyntaxTree*> argments;

            AdvanceToken("(");
            while(true) {
                argments.push_back(AssignmentExpression());
                
                if(lexer->PeakToken(0)->GetValue() == ")") {
                    break;
                }

                AdvanceToken(",");
            }
            AdvanceToken(")");

            return new CallFunctionAST(identifier, argments, GetNowLineno());
        }
        else if(lexer->PeakToken(0)->GetValue() == "new") {
            AdvanceToken("new");

            std::string name = GetVarName();
            IdentifierAST* identifier = new IdentifierAST(name, GetNowLineno());
            std::vector<AbstractSyntaxTree*> argments;

            AdvanceToken("(");
            while(!IsToken(")")) {
                argments.push_back(AssignmentExpression());
                
                if(lexer->PeakToken(0)->GetValue() == ")") {
                    break;
                }

                AdvanceToken(",");
            }
            AdvanceToken(")");

            return new MakeObjectAST(identifier, argments, GetNowLineno());
        }

        return new IdentifierAST(GetVarName(), GetNowLineno());
    }
    else if(lexer->PeakToken(0)->GetType() == String) {
        return new StringAST(lexer->ReadToken()->GetValue(), GetNowLineno());
    }

    throw std::runtime_error(UnexpectedToken(lexer->PeakToken(0)->GetValue(), GetNowLineno()));
}

AbstractSyntaxTree* Parser::DotExpression() {
    AbstractSyntaxTree* left = Factor();
    AbstractSyntaxTree* right;

    while(IsToken(".")) {
        AdvanceToken(".");
            
        right = Factor();
        left = new DotAST(left, right, GetNowLineno());
    }

    return left;
}

AbstractSyntaxTree* Parser::UnuOpExp() {
    if(IsToken("+")) {
        AdvanceToken("+");
        AbstractSyntaxTree* expression = DotExpression();

        return expression;
    }
    else if(IsToken("-")) {
        AdvanceToken("-");
        AbstractSyntaxTree* expression = DotExpression();

        return new NegativeAST(expression, GetNowLineno());
    }

    return DotExpression();
}

AbstractSyntaxTree* Parser::PowerExpression() {
    AbstractSyntaxTree* right = UnuOpExp();
    
    if(IsToken("**")) {
        AdvanceToken("**");
        AbstractSyntaxTree* left = UnuOpExp();

        return new PowerAST(right, left, GetNowLineno());
    }

    return right;
}

AbstractSyntaxTree* Parser::MultiplicationExpression() {
    AbstractSyntaxTree* left = PowerExpression();
    AbstractSyntaxTree* right;

    while(IsToken("*") || IsToken("/") || IsToken("%")) {
        if(IsToken("*")) {
            AdvanceToken("*");
            
            right = PowerExpression();
            left = new MultiplicationAST(left, right, GetNowLineno());
        }
        else if(IsToken("/")) {
            AdvanceToken("/");
            
            right = PowerExpression();
            left = new DivisionAST(left, right, GetNowLineno());
        }
        else if(IsToken("%")) {
            AdvanceToken("%");
            
            right = PowerExpression();
            left = new ModAST(left, right, GetNowLineno());
        }
    }

    return left;
}

AbstractSyntaxTree* Parser::PlusExpression() {
    AbstractSyntaxTree* left = MultiplicationExpression();
    AbstractSyntaxTree* right;

    while(IsToken("+") || IsToken("-")) {
        if(IsToken("+")) {
            AdvanceToken("+");
            
            right = MultiplicationExpression();
            left = new PlusAST(left, right, GetNowLineno());
        }
        else if(IsToken("-")) {
            AdvanceToken("-");
            
            right = MultiplicationExpression();
            left = new MinusAST(left, right, GetNowLineno());
        }
    }

    return left;
}

AbstractSyntaxTree* Parser::CompareExpression() {
    AbstractSyntaxTree* left = PlusExpression();
    AbstractSyntaxTree* right;

    while(IsToken("==") || IsToken(">") || IsToken("<") || IsToken(">=") || IsToken("<=") || IsToken("!=")) {
        if(IsToken("==")) {
            AdvanceToken("==");
            
            right = PlusExpression();
            left = new EqualAST(left, right, GetNowLineno());
        }
        else if(IsToken(">")) {
            AdvanceToken(">");
            
            right = PlusExpression();
            left = new MoreThanAST(left, right, GetNowLineno());
        }
        else if(IsToken("<")) {
            AdvanceToken("<");
            
            right = PlusExpression();
            left = new LessThanAST(left, right, GetNowLineno());
        }
        else if(IsToken(">=")) {
            AdvanceToken(">=");
            
            right = PlusExpression();
            left = new MoreThanOrEqualAST(left, right, GetNowLineno());
        }
        else if(IsToken("<=")) {
            AdvanceToken("<=");
            
            right = PlusExpression();
            left = new LessThanOrEqualAST(left, right, GetNowLineno());
        }
        else if(IsToken("!=")) {
            AdvanceToken("!=");
            
            right = PlusExpression();
            left = new NotEqualAST(left, right, GetNowLineno());
        }
    }

    return left;
}

AbstractSyntaxTree* Parser::LogicalAndExpression() {
    AbstractSyntaxTree* left = CompareExpression();
    AbstractSyntaxTree* right;

    while(IsToken("and")) {
        AdvanceToken("and");
            
        right = CompareExpression();
        left = new AndAST(left, right, GetNowLineno());
    }

    return left;
}

AbstractSyntaxTree* Parser::LogicalOrExpression() {
    AbstractSyntaxTree* left = LogicalAndExpression();
    AbstractSyntaxTree* right;

    while(IsToken("or")) {
        AdvanceToken("or");
            
        right = LogicalAndExpression();
        left = new OrAST(left, right, GetNowLineno());
    }

    return left;
}

AbstractSyntaxTree* Parser::AssignmentExpression() {
    AbstractSyntaxTree* right = LogicalOrExpression();

    if(IsToken("=")) {
        AdvanceToken("=");

        AbstractSyntaxTree* left = AssignmentExpression();

        return new AssignmentAST(right, left, GetNowLineno());
    }

    return right;
}

AbstractSyntaxTree* Parser::DeclarationStatement() {
    if(IsToken("let")) {
        AdvanceToken("let");

        std::string typeName;
        std::string varName = GetVarName();
        IdentifierAST* identifier = new IdentifierAST(varName, GetNowLineno());

        AdvanceToken(":");
        typeName = GetTypeName();

        AdvanceToken("=>");
        AbstractSyntaxTree* value = LogicalOrExpression();

        return new DeclarationAST(typeName, identifier, value, GetNowLineno());
    }
    else if(IsToken("const")) {
        AdvanceToken("const");

        std::string typeName;
        std::string varName = GetVarName();
        IdentifierAST* identifier = new IdentifierAST(varName, GetNowLineno());

        AdvanceToken(":");
        typeName = GetTypeName();

        AdvanceToken("=>");
        AbstractSyntaxTree* value = LogicalOrExpression();

        return new ConstantAST(typeName, identifier, value, GetNowLineno());
    }
    else if(IsToken("func")) {
        AdvanceToken("func");

        std::string returnTypeName;
        std::string funcName = GetVarName();
        IdentifierAST* identifier = new IdentifierAST(funcName, GetNowLineno());
        std::vector<ArgmentAST*> argments;
        std::vector<AbstractSyntaxTree*> body;
        CodeAST* code;

        AdvanceToken("(");
        while(!IsToken(")")) {
            std::string argmentName = GetVarName();
            AdvanceToken(":");
            std::string argmentType = GetTypeName();

            IdentifierAST* identifier = new IdentifierAST(argmentName, GetNowLineno());
            argments.push_back(new ArgmentAST(argmentType, identifier, GetNowLineno()));

            if(IsToken(")")) {
                break;
            }

            AdvanceToken(",");
        }
        AdvanceToken(")");

        AdvanceToken(":");
        returnTypeName = GetTypeName();

        if(!IsToken("=>")) {
            AdvanceToken("end");

            return new DefVirtualFunctionAST(returnTypeName, identifier, argments, GetNowLineno());
        }

        AdvanceToken("=>");

        while(!IsToken("end")) {
            body.push_back(OtherStatements());
        }
        AdvanceToken("end");

        code = new CodeAST(body, GetNowLineno());

        return new DefFunctionAST(returnTypeName, identifier, argments, code, GetNowLineno());
    }
    else if(IsToken("con")) {
        AdvanceToken("con");

        std::string funcName = GetVarName();
        IdentifierAST* identifier = new IdentifierAST(funcName, GetNowLineno());
        std::vector<ArgmentAST*> argments;
        std::vector<AbstractSyntaxTree*> body;
        CodeAST* code;

        AdvanceToken("(");
        while(!IsToken(")")) {
            std::string argmentName = GetVarName();
            AdvanceToken(":");
            std::string argmentType = GetTypeName();

            IdentifierAST* identifier = new IdentifierAST(argmentName, GetNowLineno());
            argments.push_back(new ArgmentAST(argmentType, identifier, GetNowLineno()));

            if(IsToken(")")) {
                break;
            }

            AdvanceToken(",");
        }
        AdvanceToken(")");

        AdvanceToken("=>");

        while(!IsToken("end")) {
            body.push_back(OtherStatements());
        }
        AdvanceToken("end");

        code = new CodeAST(body, GetNowLineno());

        return new ConstructorAST(identifier, argments, code, GetNowLineno());
    }
    else if(IsToken("des")) {
        AdvanceToken("des");

        std::string funcName = GetVarName();
        IdentifierAST* identifier = new IdentifierAST(funcName, GetNowLineno());
        std::vector<AbstractSyntaxTree*> body;
        CodeAST* code;

        AdvanceToken("(");
        AdvanceToken(")");

        if(!IsToken("=>")) {
            AdvanceToken("end");

            return new VirtualDestructorAST(identifier, GetNowLineno());
        }

        AdvanceToken("=>");

        while(!IsToken("end")) {
            body.push_back(OtherStatements());
        }
        AdvanceToken("end");

        code = new CodeAST(body, GetNowLineno());

        return new DestructorAST(identifier, code, GetNowLineno());
    }

    return AssignmentExpression();
}

AbstractSyntaxTree* Parser::ClassStatement() {
    if(IsToken("class")) {
        AdvanceToken("class");

        std::string name = GetVarName();
        IdentifierAST* identifier = new IdentifierAST(name, GetNowLineno());
        std::vector<AbstractSyntaxTree*> members;
        std::vector<AccessModifier> membersAccessModifiers;
        std::vector<std::string> inheritances;

        if(IsToken(":")) {
            AdvanceToken(":");

            while(!IsToken("=>")) {
                inheritances.push_back(lexer->ReadToken()->GetValue());

                if(IsToken("=>")) {
                    break;
                }

                AdvanceToken(",");
            }
        }

        AdvanceToken("=>");

        while(!IsToken("end")) {
            if(IsToken("public")) {
                AdvanceToken("public");
                membersAccessModifiers.push_back(AccessModifier(PUBLIC));
            }
            else if(IsToken("private")) {
                AdvanceToken("private");
                membersAccessModifiers.push_back(AccessModifier(PRIVATE));
            }
            else if(IsToken("protected")) {
                AdvanceToken("protected");
                membersAccessModifiers.push_back(AccessModifier(PROTECTED));
            }
            else {
                membersAccessModifiers.push_back(AccessModifier(PRIVATE));
            }

            members.push_back(DeclarationStatement());
        }
        AdvanceToken("end");

        return new ClassAST(identifier, inheritances, members, membersAccessModifiers, GetNowLineno());
    }
    if(IsToken("interface")) {
        AdvanceToken("interface");

        std::string name = GetVarName();
        IdentifierAST* identifier = new IdentifierAST(name, GetNowLineno());
        std::vector<AbstractSyntaxTree*> members;
        std::vector<AccessModifier> membersAccessModifiers;

        AdvanceToken("=>");

        while(!IsToken("end")) {
            if(IsToken("public")) {
                AdvanceToken("public");
                membersAccessModifiers.push_back(AccessModifier(PUBLIC));
            }
            else if(IsToken("private")) {
                AdvanceToken("private");
                membersAccessModifiers.push_back(AccessModifier(PRIVATE));
            }
            else if(IsToken("protected")) {
                AdvanceToken("protected");
                membersAccessModifiers.push_back(AccessModifier(PROTECTED));
            }
            else {
                membersAccessModifiers.push_back(AccessModifier(PRIVATE));
            }

            members.push_back(DeclarationStatement());
        }
        AdvanceToken("end");

        return new InterfaceAST(identifier, members, membersAccessModifiers, GetNowLineno());
    }

    return DeclarationStatement();
}

AbstractSyntaxTree* Parser::OtherStatements() {
    if(IsToken("if")) {
        AdvanceToken("if");
        AdvanceToken("(");

        AbstractSyntaxTree* expression = AssignmentExpression();

        AdvanceToken(")");
        
        CodeAST* block = GetBlock();

        return new IfAST(expression, block, GetNowLineno());
    }
    else if(IsToken("elif")) {
        AdvanceToken("elif");
        AdvanceToken("(");

        AbstractSyntaxTree* expression = AssignmentExpression();

        AdvanceToken(")");
        
        CodeAST* block = GetBlock();

        return new ElifAST(expression, block, GetNowLineno());
    }
    else if(IsToken("else")) {
        AdvanceToken("else");

        CodeAST* block = GetBlock();

        return new ElseAST(block, GetNowLineno());
    }
    else if(IsToken("for")) {
        AdvanceToken("for");
        AdvanceToken("(");

        AbstractSyntaxTree* expression1 = DeclarationStatement();
        AdvanceToken(",");
        AbstractSyntaxTree* expression2 = LogicalOrExpression();
        AdvanceToken(",");
        AbstractSyntaxTree* expression3 = AssignmentExpression();

        AdvanceToken(")");
        
        CodeAST* block = GetBlock();

        return new ForAST(expression1, expression2, expression3, block, GetNowLineno());
    }
    else if(IsToken("while")) {
        AdvanceToken("while");
        AdvanceToken("(");

        AbstractSyntaxTree* expression = AssignmentExpression();

        AdvanceToken(")");
        
        CodeAST* block = GetBlock();

        return new WhileAST(expression, block, GetNowLineno());
    }
    else if(IsToken("break")) {
        AdvanceToken("break");

        return new BreakAST(GetNowLineno());
    }
    else if(IsToken("continue")) {
        AdvanceToken("continue");

        return new ContinueAST(GetNowLineno());
    }
    else if(IsToken("return")) {
        AdvanceToken("return");

        AbstractSyntaxTree* returnValue = AssignmentExpression();

        return new ReturnAST(returnValue, GetNowLineno());
    }
    else if(IsToken("include")) {
        AdvanceToken("include");

        AbstractSyntaxTree* fileName = Factor();

        if(IsToken(":")) {
            AdvanceToken(":");

            if(IsToken("H")) {
                AdvanceToken("H");

                return new IncludeAST(fileName, true, false, GetNowLineno());
            }
            else if(IsToken("F")) {
                AdvanceToken("F");

                return new IncludeAST(fileName, false, false, GetNowLineno());
            }
        }

        return new IncludeAST(fileName, false, true, GetNowLineno());
    }
    else if(IsToken("neitive")) {
        AdvanceToken("neitive");

        AbstractSyntaxTree* block = GetBlock();

        return new NeitiveCodeAST(block->GetChild(0)->OutputCode(), GetNowLineno());
    }

    return ClassStatement();
}

AbstractSyntaxTree* Parser::Code() {
    std::vector<AbstractSyntaxTree*> expressions;
    while(!IsToken("EOF")) {
        expressions.push_back(OtherStatements());
    }

    return new CodeAST(expressions, GetNowLineno());
}