#include "syntaxtree.h"

SyntaxTree::SyntaxTree()
    : m_label(Labels::Tags::Leaf)
    , m_code(-1)
{
}

SyntaxTree::SyntaxTree(int code)
    : m_label(Labels::Tags::Leaf)
    , m_code(code)
{
}

void SyntaxTree::addChild(std::shared_ptr<SyntaxTree> child)
{
    m_childrens.push_back(child);
}

void SyntaxTree::addChild(int code)
{
    m_childrens.push_back(std::make_shared<SyntaxTree>(code));
}

std::vector<std::shared_ptr<SyntaxTree>> &SyntaxTree::childrens()
{
    return m_childrens;
}

Labels::Tags SyntaxTree::label() const
{
    return m_label;
}

int SyntaxTree::code() const
{
    return m_code;
}
