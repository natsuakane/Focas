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
    "interface BBB => \n"
    "\n"
    "   public func a(b : ref int) : int end\n"
    "   public des BBB() end\n"
    "end\n"
    "\n"
    "class AAA : BBB => \n" 
    "\n"
    "   public con AAA(a : ref int) =>\n"
    "       for(let a : int = 0, i +10, i = i + 1) =>\n"
    "           ref a = ref a\n"
    "       end\n"
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