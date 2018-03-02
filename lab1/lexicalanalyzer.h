#ifndef LEXICALANALYZER_H
#define LEXICALANALYZER_H

#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "token.h"

class LexicalAnalyzer
{
    enum Attributes {
        Whitespace = 0,
        Constant = 1,
        Identifier = 2,
        Separator = 3,
        Multichar = 4,
        Comment = 5,
        Invalid = 6
    };
    enum TabRanges {
        keywordsBegin = 300,
        identifiersBegin = 400,
        constantsBegin = 600
    };
    struct Symbol {
        char value;
        Attributes attr;
    };

    int attributes[128] = {
        6, 6, 6, 6, 6, 6, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 5, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 41, 41, 42, 42, 42,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
    };

    std::vector<Token*> m_Tokens;

    std::map<std::string,int> *keywordsTable;
    std::map<std::string,int> *identifiersTable;
    std::map<std::string,int> *constantsTable;

public:
    LexicalAnalyzer(std::map<std::string,int> *keyword, std::map<std::string,int> *identifiers, std::map<std::string,int> *constants);
    std::vector<Token*> analyze(std::ifstream &stream);

private:
    Symbol gets(std::ifstream &stream);
    int search(std::map<std::string,int> *table, std::string &token);
    int append(std::map<std::string,int> *table, int RangeBegin, std::string token);
};

#endif // LEXICALANALYZER_H
