#pragma once

#include <string>
#include <vector>
#include <memory>
#include <map>

#include "labels.h"

class SyntaxTree
{
public:
    SyntaxTree();
    void addChild(std::shared_ptr<SyntaxTree> child);
    std::vector<std::shared_ptr<SyntaxTree>> &childrens();

private:
    std::weak_ptr<SyntaxTree> m_parent;
    std::vector<std::shared_ptr<SyntaxTree>> m_childrens;

    Labels::Tags m_label;
};
