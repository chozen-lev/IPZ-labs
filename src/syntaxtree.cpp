#include "syntaxtree.h"

SyntaxTree::SyntaxTree()
{

}

void SyntaxTree::addChild(std::shared_ptr<SyntaxTree> child)
{
    m_childrens.push_back(child);
}

std::vector<std::shared_ptr<SyntaxTree>> &SyntaxTree::childrens()
{
    return m_childrens;
}
