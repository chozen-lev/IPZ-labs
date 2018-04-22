#pragma once

#include <string>

struct Position
{
    Position(int colomn, int line) :
        m_colomn(colomn),
        m_line(line)
    {
    }
    int x() { return m_colomn; }
    int y() { return m_line; }

private:
    int m_colomn;
    int m_line;
};

struct Token
{
    Token(std::string name, int code, Position pos) :
        m_tokenName(name),
        m_tokenCode(code),
        m_tokenPosition(pos)
    {
    }
    std::string name() { return m_tokenName; }
    int code() { return m_tokenCode; }
    int x() { return m_tokenPosition.x(); }
    int y() { return m_tokenPosition.y(); }

private:
    std::string m_tokenName;
    int m_tokenCode;
    Position m_tokenPosition;
};
