#pragma once

#include <vector>
#include <memory>
#include <map>
#include <functional>

#include "token.h"
#include "syntaxtree.h"

class Parser
{
public:
    Parser();

    std::shared_ptr<SyntaxTree> analyze(std::vector<std::shared_ptr<Token>> &tokens,
                                        std::map<std::string, int> &keywords,
                                        std::map<std::string, int> &identifiers,
                                        std::map<std::string, int> &constans,
                                        std::vector<std::string> &errors);

private:
    std::map<Labels::Tags, std::function<void(std::shared_ptr<SyntaxTree>)>> m_labelsFunction;

    void signalProgram(std::shared_ptr<SyntaxTree> node);
    void program(std::shared_ptr<SyntaxTree> node);
    void procedureIdentifier(std::shared_ptr<SyntaxTree> node);
    void block(std::shared_ptr<SyntaxTree> node);
    void parametersList(std::shared_ptr<SyntaxTree> node);
    void declarations(std::shared_ptr<SyntaxTree> node);
    void statementsList(std::shared_ptr<SyntaxTree> node);
    void labelDeclarations(std::shared_ptr<SyntaxTree> node);
    void unsignedInteger(std::shared_ptr<SyntaxTree> node);
    void labelsList(std::shared_ptr<SyntaxTree> node);
    void empty(std::shared_ptr<SyntaxTree> node);
    void identidier(std::shared_ptr<SyntaxTree> node);
};
