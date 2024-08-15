#include <string>

std::string ExpectedCharacter(char expected, int lineno, int codePointerInLine){
    return "Error: The character \"" + std::string(1, expected) + 
            "\" is unexpected at this point." + 
            std::to_string(lineno) + ":" + std::to_string(codePointerInLine);
}