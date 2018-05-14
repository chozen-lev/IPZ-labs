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

SyntaxTree::SyntaxTree(Labels::Tags label)
    : m_label(label)
    , m_code(-1)
{
}

std::shared_ptr<SyntaxTree> &SyntaxTree::addChild(std::shared_ptr<SyntaxTree> &child)
{
    m_childrens.push_back(child);
    return child;
}

std::shared_ptr<SyntaxTree> &SyntaxTree::addChild(int code)
{
    m_childrens.push_back(std::make_shared<SyntaxTree>(code));
    return m_childrens.back();
}

std::shared_ptr<SyntaxTree> &SyntaxTree::addChild(Labels::Tags label)
{
    m_childrens.push_back(std::make_shared<SyntaxTree>(label));
    return m_childrens.back();
}

std::vector<std::shared_ptr<SyntaxTree>> &SyntaxTree::childrens()
{
    return m_childrens;
}

SyntaxTree &SyntaxTree::at(int index)
{
    return *m_childrens.at(index).get();
}

Labels::Tags SyntaxTree::label() const
{
    return m_label;
}

int SyntaxTree::code() const
{
    return m_code;
}

void SyntaxTree::setLabel(Labels::Tags label)
{
    m_label = label;
}
