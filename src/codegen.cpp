#include "codegen.h"

CodeGen::CodeGen()
{
}

std::string CodeGen::generate(SyntaxTree root, Tables tables, Errors &errors)
{
    if (!errors.empty()) {
        return "";
    }

    m_identifierList.clear();
    std::string codeText = signalProgram(root, tables, errors) + "\n";

    return errors.empty() ? codeText : "";
}

std::string CodeGen::signalProgram(SyntaxTree node, Tables tables, Errors &errors)
{
    return program(node.at(0), tables, errors);
}

std::string CodeGen::program(SyntaxTree node, Tables tables, Errors &errors)
{
    std::string programText;
    int typeCode = node.at(0).code();

    std::string identifierText = procedureIdentifier(node.at(1), tables, errors);

    if (typeCode == PROGRAM_CODE) {
        programText += identifierText + " segment\n";
        programText += block(node.at(3), tables, errors) + "\n";
        programText += identifierText + " ends\n";
        programText += "end";
    } else if (typeCode == PROCEDURE_CODE) {
        std::string parametersListText = parametersList(node.at(2), tables, errors);

        programText += "public " + identifierText + "\n";
        programText += "Code segment\n";
        programText += identifierText + " proc " + parametersListText + "\n";
        programText += block(node.at(4), tables, errors) + "\n";
        programText += identifierText + " endp\n";
        programText += "Code ends\n";
        programText += "end";
    }

    return programText;
}

std::string CodeGen::procedureIdentifier(SyntaxTree node, Tables tables, Errors &)
{
    std::string identifier = "?" + tables.name(node.at(0).at(0).code());
    m_identifierList.push_back(identifier);
    return identifier;
}

std::string CodeGen::block(SyntaxTree node, Tables tables, Errors &errors)
{
    std::string blockText = declarations(node.at(0), tables, errors);
    blockText += statementsList(node.at(2), tables, errors);

    return blockText;
}

std::string CodeGen::parametersList(SyntaxTree node, Tables tables, Errors &errors)
{
    return declarationsList(node.at(1), tables, errors);
}

std::string CodeGen::declarations(SyntaxTree node, Tables tables, Errors &errors)
{
    labelDeclarations(node.at(0), tables, errors);
    return "";
}

std::string CodeGen::declarationsList(SyntaxTree, Tables, Errors &)
{
    return "";
}

std::string CodeGen::statementsList(SyntaxTree, Tables, Errors &)
{
    return "";
}

std::string CodeGen::labelDeclarations(SyntaxTree node, Tables tables, Errors &errors)
{
    auto begin = std::begin(m_identifierList);
    auto end = std::end(m_identifierList);
    std::string labelText = "?" + unsignedInteger(node.at(1), tables, errors);

    if (std::find(begin, end, labelText) != end) {
        return "";
    }

    m_identifierList.push_back(labelText);

    labelsList(node.at(2), tables, errors);
    return "";
}

std::string CodeGen::unsignedInteger(SyntaxTree node, Tables tables, Errors &)
{
    return tables.name(node.at(0).code());
}

std::string CodeGen::labelsList(SyntaxTree node, Tables tables, Errors &errors)
{
    if (node.at(0).label() == Labels::Tags::Empty) {
        return "";
    }

    auto begin = std::begin(m_identifierList);
    auto end = std::end(m_identifierList);
    std::string labelText = "?" + unsignedInteger(node.at(1), tables, errors);

    if (std::find(begin, end, labelText) != end) {
        errors.push_back(std::string("\033[1;37mCode Generator:\033[0m \033[1;31mError:\033[0m ")
                         + "redeclaration of '" + labelText.substr(1) + "'");
        return "";
    }

    m_identifierList.push_back(labelText);
    labelsList(node.at(2), tables, errors);

    return "";
}
