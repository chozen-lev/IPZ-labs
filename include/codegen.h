#pragma once

#include <string>
#include <vector>
#include <map>

#include "tables.h"
#include "syntaxtree.h"

class CodeGen
{
public:
    using TokenIterator = Tables::TokenIterator;
    using Errors = std::vector<std::string>;

    CodeGen();

    std::string generate(SyntaxTree root, Tables tables, Errors &errors);
private:

    std::string signalProgram(SyntaxTree node, Tables tables, Errors &errors);
    std::string program(SyntaxTree node, Tables tables, Errors &errors);
    std::string procedureIdentifier(SyntaxTree node, Tables tables, Errors &errors);
    std::string block(SyntaxTree node, Tables tables, Errors &errors);
    std::string parametersList(SyntaxTree node, Tables tables, Errors &errors);
    std::string declarations(SyntaxTree node, Tables tables, Errors &errors);
    std::string declarationsList(SyntaxTree node, Tables tables, Errors &errors);
    std::string statementsList(SyntaxTree node, Tables tables, Errors &errors);
    std::string labelDeclarations(SyntaxTree node, Tables tables, Errors &errors);
    std::string unsignedInteger(SyntaxTree node, Tables tables, Errors &errors);
    std::string labelsList(SyntaxTree node, Tables tables, Errors &errors);

private:
    std::vector<std::string> m_identifierList;
};
