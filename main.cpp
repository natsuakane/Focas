#include "Token.h"
#include "IdentifierToken.h"
#include "NumberToken.h"
#include "OperatorToken.h"
#include "EOLToken.h"
#include "Lexer.h"
#include "NumberAST.h"
#include "FloatNumberAST.h"
#include "PlusAST.h"
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

    FloatNumberAST* number1 = new FloatNumberAST(100, 0);
    FloatNumberAST* number2 = new FloatNumberAST(100, 0);
    PlusAST* plus = new PlusAST(number1, number2, 0);
    std::cout << plus->Execute()->GetDouble() << std::endl;

    return 0;
}