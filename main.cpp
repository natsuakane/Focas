#include "Token.h"
#include "IdentifierToken.h"
#include "NumberToken.h"
#include "OperatorToken.h"
#include "EOLToken.h"
#include "Lexer.h"
#include "NumberAST.h"
#include "FloatNumberAST.h"
#include "PlusAST.h"
#include "MultiplicationAST.h"
#include "IdentifierAST.h"
#include "ConstantAST.h"
#include "StringAST.h"
#include "Parser.h"
#include <iostream>
#include <regex>

int main(){
    std::string codeStr = 
    "class AAA => \n" 
    "   public con AAA(a : int) =>\n"
    "       a=a\n"
    "   end\n" 
    "   public func a(a : int) : int =>\n"
    "       b + 10\n" 
    "   end\n"
    "   public des AAA() =>\n"
    "       print(a)\n"
    "   end\n"
    "end\n" 
    "let a : ref AAA = new AAA(10)\n";
    Lexer lexer(codeStr);

    Parser parser(&lexer);
    AbstractSyntaxTree* code = parser.GetTree();
    std::cout << code->OutputCode() << std::endl;

    return 0;
}