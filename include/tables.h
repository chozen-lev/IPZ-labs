#pragma once

#include <string>
#include <map>
#include <algorithm>

#include "token.h"

class Tables
{
public:
    enum class Range : int {
        keywordsBegin = 300,
        identifiersBegin = 500,
        constantsBegin = 700
    };

public:
    Tables();
    int search(Range rangeBegin, std::string &token) const;
    int append(Range rangeBegin, std::string &token);
    std::map<std::string, int> &table(Range rangeBegin);
    std::map<std::string, int> &table(int code);

private:
    std::map<std::string, int> m_keywords;
    std::map<std::string, int> m_identifiers;
    std::map<std::string, int> m_constants;
};
