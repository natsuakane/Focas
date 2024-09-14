#pragma once

#include <string>

std::string ExpectedCharacter(char expected, int lineno, int codePointerInCode) {
    return "Error: The character \"" + std::string(1, expected) + 
            "\" is undefined token. " + 
            std::to_string(lineno) + ":" + std::to_string(codePointerInCode);
}

std::string UnsuitableType(std::string typeName, std::string correctTypeName, int lineno) {
    return "Error: The type \"" + typeName + 
            "\" is unsuitable type at this point. " + 
            "This type is \"" + correctTypeName + "\". " + 
            std::to_string(lineno);
}

std::string UnsuitableTypeWithOperator(std::string op, std::string argmentType, int lineno) {
    return "Error: The argment type \"" + argmentType + 
            "\" cannot be executed by the operator \"" + op + "\". " + 
            std::to_string(lineno);
}

std::string UnexpectedToken(std::string token, int lineno) {
    return "Error: The token \"" + token + "\" is unexpected token. " + std::to_string(lineno);
}

std::string TypeHasNoChildren(std::string type, int lineno) {
    return "Error: The type \"" + type + "\" has no children. " + std::to_string(lineno);
}

std::string TypeHasNoChildrenMoreThan(std::string type, int n, int lineno) {
    return "Error: The type \"" + type + "\" has no children more than " + std::to_string(n)
            + ". " + std::to_string(lineno);
}

std::string CantOpenTheFile(std::string fileName) {
    return "Error: Can't open the file \"" + fileName + "\".";
}