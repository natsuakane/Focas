#include <string>

std::string ExpectedCharacter(char expected, int lineno, int codePointerInCode){
    return "Error: The character \"" + std::string(1, expected) + 
            "\" is undefined token." + 
            std::to_string(lineno) + ":" + std::to_string(codePointerInCode);
}

std::string UnsuitableType(std::string typeName, int lineno){
    return "Error: The type \"" + typeName + 
            "\" is unsuitable type at this point" + 
            std::to_string(lineno);
}