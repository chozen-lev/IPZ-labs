#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include "token.h"

class Listing
{
public:
    Listing();

    void printErrors(std::vector<std::string> errors, std::ostream &stream = std::cout);
    void printTokens(std::vector<std::shared_ptr<Token>> tokens, std::ostream &stream = std::cout);
};
