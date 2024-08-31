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
        "public con AAA(a : int) => a=a end\n" 
        "public func a(a : int) : int => b + 10 end\n"
        "public des AAA() => print(a) end\n"
    "end\n" 
    "let a : AAA = new AAA(10)\n";
    Lexer lexer(codeStr);

    Parser parser(&lexer);
    AbstractSyntaxTree* code = parser.GetTree();
    std::cout << code->OutputCode() << std::endl;

    return 0;
}