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
    explicit SyntaxTree(int code);
    explicit SyntaxTree(Labels::Tags label);

    std::shared_ptr<SyntaxTree> &addChild(std::shared_ptr<SyntaxTree> &child);
    std::shared_ptr<SyntaxTree> &addChild(int code);
    std::shared_ptr<SyntaxTree> &addChild(Labels::Tags label);

    std::vector<std::shared_ptr<SyntaxTree>> &childrens();
    SyntaxTree& at(int index);
    Labels::Tags label() const;
    int code() const;

    void setLabel(Labels::Tags label);

private:
    std::vector<std::shared_ptr<SyntaxTree>> m_childrens;

    Labels::Tags m_label;
    int m_code;
};
