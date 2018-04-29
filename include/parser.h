#pragma once

#include <vector>
#include <memory>
#include <map>
#include <functional>

#include "token.h"
#include "labels.h"
#include "tables.h"
#include "syntaxtree.h"

class Parser
{
public:
    Parser();

    std::shared_ptr<SyntaxTree> analyze(Tables &tables, std::vector<std::string> &errors);

private:
    bool signalProgram(auto &node, auto &token, auto end, auto &tables, auto &errors);
    bool program(auto &node, auto &token, auto end, auto &tables, auto &errors);
    bool procedureIdentifier(auto &node, auto &token, auto end, auto &tables, auto &errors);
    bool block(auto &node, auto &token, auto end, auto &tables, auto &errors);
    bool parametersList(auto &node, auto &token, auto end, auto &tables, auto &errors);
    bool declarations(auto &node, auto &token, auto end, auto &tables, auto &errors);
    bool declarationsList(auto &node, auto &token, auto end, auto &tables, auto &errors);
    bool statementsList(auto &node, auto &token, auto end, auto &tables, auto &errors);
    bool labelDeclarations(auto &node, auto &token, auto end, auto &tables, auto &errors);
    bool unsignedInteger(auto &node, auto &token, auto end, auto &tables, auto &errors);
    bool labelsList(auto &node, auto &token, auto end, auto &tables, auto &errors);
    bool identidier(auto &node, auto &token, auto end, auto &tables, auto &errors);
    bool leaf(auto &node, auto &token, auto end, auto &tables, auto &errors,
              int code = -1, Tables::Range range = static_cast<Tables::Range>(0), bool required = true);
};
