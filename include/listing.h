#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include "token.h"
#include "tables.h"
#include "syntaxtree.h"

class Listing
{
public:
    Listing();

    void printErrors(std::vector<std::string> errors, std::ostream &stream = std::cout) const;
    void printTokens(std::vector<std::shared_ptr<Token>> tokens, std::ostream &stream = std::cout) const;
    void printSyntaxTree(std::shared_ptr<SyntaxTree> node,
                         Tables tables,
                         std::ostream &stream = std::cout,
                         int level = 0) const;
};
