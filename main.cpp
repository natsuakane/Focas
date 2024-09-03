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
    "\n"
    "   public con AAA(a : ref int) =>\n"
    "       ref a = ref a\n"
    "   end\n" 
    "\n"
    "   public func a(b : ref int) : int =>\n"
    "       ref b + (-10)\n" 
    "   end\n"
    "\n"
    "   public des AAA() =>\n"
    "       print(a)\n"
    "   end\n"
    "end\n"
    "let i : int = 10\n"
    "let a : ref AAA = new AAA(add i)\n";
    Lexer lexer(codeStr);

    Parser parser(&lexer);
    AbstractSyntaxTree* code = parser.GetTree();
    std::cout << code->OutputCode() << std::endl;

    return 0;
}