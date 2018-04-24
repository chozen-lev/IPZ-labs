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
    SyntaxTree(int code);

    void addChild(std::shared_ptr<SyntaxTree> child);
    void addChild(int code);

    std::vector<std::shared_ptr<SyntaxTree>> &childrens();
    Labels::Tags label() const;
    int code() const;

private:
    std::vector<std::shared_ptr<SyntaxTree>> m_childrens;

    Labels::Tags m_label;
    int m_code;
};
