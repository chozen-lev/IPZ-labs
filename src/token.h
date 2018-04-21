#pragma once

#include <string>

struct Token
{
    std::string m_tokenName;
    int m_tokenType;
    int m_tokenPosition;
    int m_linePosition;

public:
    std::string name() { return m_tokenName; }
    int type() { return m_tokenType; }
    int x() { return m_tokenPosition; }
    int y() { return m_linePosition; }
};
