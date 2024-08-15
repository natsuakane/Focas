#include "Token.h"
#include "IdentifierToken.h"
#include "NumberToken.h"
#include "OperatorToken.h"
#include "EOLToken.h"
#include "Lexer.h"
#include <iostream>
#include <regex>

int main(){
    std::cout << "Hello, Unchi!" << std::endl;
    
    Lexer lexer("a32+200.5*=\n500\n");
    std::cout << lexer.ReadToken()->GetValue() << std::endl;
    std::cout << lexer.ReadToken()->GetValue() << std::endl;
    std::cout << lexer.ReadToken()->GetValue() << std::endl;
    std::cout << lexer.ReadToken()->GetValue() << std::endl;
    std::cout << lexer.ReadToken()->GetValue() << std::endl;
    std::cout << lexer.ReadToken()->GetValue() << std::endl;
    std::cout << lexer.ReadToken()->GetValue() << std::endl;
    std::cout << lexer.ReadToken()->GetValue() << std::endl;

    return 0;
}