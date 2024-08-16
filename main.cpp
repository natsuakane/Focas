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
#include <iostream>
#include <regex>

int main(){
    std::cout << "Hello, Unchi!" << std::endl;
    
    Lexer lexer("a32+200.5*100\n500\n");
    std::cout << lexer.ReadToken()->GetValue() << std::endl;
    std::cout << lexer.ReadToken()->GetValue() << std::endl;
    std::cout << lexer.ReadToken()->GetValue() << std::endl;
    std::cout << lexer.ReadToken()->GetValue() << std::endl;
    std::cout << lexer.ReadToken()->GetValue() << std::endl;
    std::cout << lexer.ReadToken()->GetValue() << std::endl;
    std::cout << lexer.ReadToken()->GetValue() << std::endl;
    std::cout << lexer.ReadToken()->GetValue() << std::endl;

    std::cout << std::endl;

    NumberAST* number1 = new NumberAST(100, 0);
    FloatNumberAST* number2 = new FloatNumberAST(100.5, 0);
    NumberAST* number3 = new NumberAST(5, 0);
    PlusAST* plus = new PlusAST(number1, new MultiplicationAST(number2, number3, 0), 0);
    std::cout << plus->OutputCode() << std::endl;

    return 0;
}