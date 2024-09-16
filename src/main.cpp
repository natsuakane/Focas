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
#include "Exceptions.h"
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <regex>

std::vector<std::string> split_naive(const std::string &s, char delim) {
    std::vector<std::string> elems;
    std::string item;
    for (int i = 0; i < s.size(); i++) {
        char ch = s[i];

        if (ch == delim) {
            if (!item.empty())
                elems.push_back(item);
            item.clear();
        }
        else {
            item += ch;
        }
    }
    if (!item.empty())
        elems.push_back(item);
    return elems;
}

std::string ReadFile(std::string fileName) {
    std::ifstream file(fileName);

    if(file.fail()) {
        std::cerr << CantOpenTheFile(fileName) << std::endl;
    }

    std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    return str;
}

void WriteFile(std::string fileName, std::string content) {
    std::ofstream file(fileName);

    if(file.fail()) {
        std::cerr << CantOpenTheFile(fileName) << std::endl;
    }

    file << content << std::endl;
}

int main(int argc, char* argv[]){
    std::vector<std::string> inputFileNames;
    std::vector<std::string> outputFileNames;

    bool isHeaderFile = false;
    bool isCOption = false;

    int i, opt;
    while((opt = getopt(argc, argv, "hco:")) != -1) {
        switch(opt) {
            case 'h':
                isHeaderFile = true;
                break;
            case 'c':
                isCOption = true;
                break;
            case 'o':
                outputFileNames.push_back(optarg);
                break;
        }
    }

    while(optind < argc) {
        inputFileNames.push_back(argv[optind]);

        if(outputFileNames.size() >= inputFileNames.size()) continue;

        std::vector<std::string> SplitedInputFileName = split_naive(inputFileNames.back(), '.');
        std::vector<std::string> SlicedInPutFileName;
        SlicedInPutFileName.resize(SplitedInputFileName.size() - 1);
        std::copy(SplitedInputFileName.begin(), SplitedInputFileName.end() - 1, SlicedInPutFileName.begin());

        std::string outputFileName;
        for(int i = 0; i < SlicedInPutFileName.size(); i++) {
            outputFileName += SlicedInPutFileName[i];
            outputFileName += ".";
        }
        outputFileName += isHeaderFile ? "h" : "cpp";

        outputFileNames.push_back(outputFileName);

        optind++;
    }

    for(int i = 0; i < inputFileNames.size(); i++) {
        if(i > 0 && !isCOption) {
            break;
        }

        std::string codeStr = ReadFile(inputFileNames[i]) + "\n";
        Lexer lexer(codeStr);
        Parser parser(&lexer);
        AbstractSyntaxTree* code = parser.GetTree();

        WriteFile(outputFileNames[0], code->OutputCode());
    }

    return 0;
}