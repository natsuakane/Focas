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
#include "DeclarationAST.h"
#include "Parser.h"
#include <iostream>
#include <regex>

int main(){
    std::cout << "Hello, Unchi!" << std::endl;
    
    Lexer lexer("3 + a32 * 200.5 * 7 + 7\n");

    Parser parser(&lexer);
    std::cout << parser.GetTree()->OutputCode() << std::endl;

    return 0;
}