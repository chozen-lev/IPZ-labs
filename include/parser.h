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
    struct Builder {
        Builder(std::shared_ptr<SyntaxTree> &_node, Tables &_tables)
            : node(_node)
            , tables(_tables)
        {
        }

        std::shared_ptr<SyntaxTree> node;
        Tables tables;
    };

public:
    Parser();

    std::shared_ptr<SyntaxTree> analyze(Tables &tables, std::vector<std::string> &errors);

private:
    using TokenIterator = Tables::TokenIterator;

    bool signalProgram(Builder builder, TokenIterator &tokens, std::vector<std::string> &errors);
    bool program(Builder builder, TokenIterator &tokens, std::vector<std::string> &errors);
    bool procedureIdentifier(Builder builder, TokenIterator &tokens, std::vector<std::string> &errors);
    bool block(Builder builder, TokenIterator &tokens, std::vector<std::string> &errors);
    bool parametersList(Builder builder, TokenIterator &tokens, std::vector<std::string> &errors);
    bool declarations(Builder builder, TokenIterator &tokens, std::vector<std::string> &errors);
    bool declarationsList(Builder builder, TokenIterator &tokens, std::vector<std::string> &errors);
    bool statementsList(Builder builder, TokenIterator &tokens, std::vector<std::string> &errors);
    bool labelDeclarations(Builder builder, TokenIterator &tokens, std::vector<std::string> &errors);
    bool unsignedInteger(Builder builder, TokenIterator &tokens, std::vector<std::string> &errors);
    bool labelsList(Builder builder, TokenIterator &tokens, std::vector<std::string> &errors);
    bool identidier(Builder builder, TokenIterator &tokens, std::vector<std::string> &errors);
    bool leaf(Builder builder, TokenIterator &tokens, std::vector<std::string> &errors, int code = -1,
              Tables::Range range = static_cast<Tables::Range>(0), bool required = true);
};
