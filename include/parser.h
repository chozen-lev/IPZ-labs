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

    std::shared_ptr<SyntaxTree> analyze(std::vector<std::shared_ptr<Token>> &tokens,
                                        Tables tables,
                                        std::vector<std::string> &errors);

private:
    std::map<Labels::Tags,
    std::function<bool(std::shared_ptr<SyntaxTree>)>> m_labelsFunction;

    bool signalProgram(std::shared_ptr<SyntaxTree> node);
    bool program(std::shared_ptr<SyntaxTree> node);
    bool procedureIdentifier(std::shared_ptr<SyntaxTree> node);
    bool block(std::shared_ptr<SyntaxTree> node);
    bool parametersList(std::shared_ptr<SyntaxTree> node);
    bool declarations(std::shared_ptr<SyntaxTree> node);
    bool statementsList(std::shared_ptr<SyntaxTree> node);
    bool labelDeclarations(std::shared_ptr<SyntaxTree> node);
    bool unsignedInteger(std::shared_ptr<SyntaxTree> node);
    bool labelsList(std::shared_ptr<SyntaxTree> node);
    bool empty(std::shared_ptr<SyntaxTree> node);
    bool identidier(std::shared_ptr<SyntaxTree> node);
};
