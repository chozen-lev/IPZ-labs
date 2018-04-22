#pragma once

#include <vector>
#include <memory>

#include "token.h"

class Parser
{
public:
    Parser();

    void analyze(std::vector<std::shared_ptr<Token>> tokens);
};
