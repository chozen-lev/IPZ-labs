#pragma once

#include <fstream>
#include <memory>
#include <vector>
#include <map>

#include "token.h"

#define ASCII_SIZE 128

class Scanner
{
    enum Attr : int {
        Invalid = 0,
        Whitespace,
        Constant,
        Identifier,
        Separator,
        Comment,
//        Multichar,
    };
    enum class TablesRange : int {
        keywordsBegin = 300,
        identifiersBegin = 500,
        constantsBegin = 700
    };

    struct Symbol {
        // pre-defined attributes for ascii symbols
        Attr const asciiAttr[ASCII_SIZE] =  {
            Invalid, Invalid, Invalid, Invalid, Invalid, Invalid, Invalid, Invalid, Invalid, Whitespace,
            Whitespace, Whitespace, Whitespace, Whitespace, Invalid, Invalid, Invalid, Invalid, Invalid, Invalid,
            Invalid, Invalid, Invalid, Invalid, Invalid, Invalid, Invalid, Invalid, Invalid, Invalid,
            Invalid, Invalid, Whitespace, Invalid, Invalid, Invalid, Invalid, Invalid, Invalid, Invalid,
            Comment, Separator, Invalid, Separator, Separator, Invalid, Separator, Invalid, Constant, Constant,
            Constant, Constant, Constant, Constant, Constant, Constant, Constant, Constant, Invalid, Separator,
            Invalid, Invalid, Invalid, Invalid, Invalid, Identifier, Identifier, Identifier, Identifier, Identifier,
            Identifier, Identifier, Identifier, Identifier, Identifier, Identifier, Identifier, Identifier, Identifier, Identifier,
            Identifier, Identifier, Identifier, Identifier, Identifier, Identifier , Identifier, Identifier, Identifier, Identifier,
            Identifier, Invalid, Invalid, Invalid, Invalid, Invalid, Invalid, Identifier, Identifier, Identifier,
            Identifier, Identifier, Identifier, Identifier, Identifier, Identifier, Identifier, Identifier, Identifier, Identifier,
            Identifier, Identifier, Identifier, Identifier, Identifier, Identifier, Identifier, Identifier, Identifier, Identifier,
            Identifier, Identifier, Identifier, Invalid, Invalid, Invalid, Invalid, Invalid
        };

        char value;
        Attr attr;

        Symbol() : value(char(0)), attr(Invalid) {}
        void gets(std::ifstream &stream);
    };

public:
    Scanner();

    std::vector<std::shared_ptr<Token>> analyze(std::ifstream &stream,
                                                std::map<std::string, int> &keywords,
                                                std::map<std::string, int> &identifiers,
                                                std::map<std::string, int> &constans,
                                                std::vector<std::string> &errors);

private:
    int search(std::map<std::string, int> &table, std::string &token);
    int append(std::map<std::string, int> &table, TablesRange rangeBegin, std::string &token);
};
