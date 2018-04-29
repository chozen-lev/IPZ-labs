#pragma once

#include <fstream>
#include <memory>
#include <vector>
#include <map>

#include "token.h"
#include "tables.h"

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

    void analyze(std::ifstream &stream, Tables &tables, std::vector<std::string> &errors);
};
