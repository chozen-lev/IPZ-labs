#pragma once

#include <string>
#include <map>
#include <algorithm>
#include <vector>
#include <memory>

#include "token.h"

#define PROGRAM_CODE 300
#define PROCEDURE_CODE 301
#define BEGIN_CODE 302
#define END_CODE 303
#define LABEL_CODE 304

class Tables
{
public:
    enum class Range : int {
        keywordsBegin = 300,
        identifiersBegin = 500,
        constantsBegin = 700
    };

    struct TokenIterator {
        explicit TokenIterator(std::vector<std::shared_ptr<Token>> &tokens)
            : token(std::begin(tokens))
            , end(std::end(tokens))
        {
        }

        std::vector<std::shared_ptr<Token>>::iterator token;
        std::vector<std::shared_ptr<Token>>::const_iterator end;
    };

public:
    Tables();
    int search(Range rangeBegin, std::string name);
    int append(Range rangeBegin, std::string name);
    std::map<std::string, int> &table(Range rangeBegin);
    std::map<std::string, int> &table(int code);
    std::string name(int code);

    void addToken(Token token);
    std::vector<std::shared_ptr<Token>> &tokens();

    Range getRange(int code) const;

private:
    std::map<std::string, int> m_keywords;
    std::map<std::string, int> m_identifiers;
    std::map<std::string, int> m_constants;

    std::vector<std::shared_ptr<Token>> m_tokens;
};
