#include "parser.h"

Parser::Parser()
{
    using lt = Labels::Tags;
    using shared_tree = std::shared_ptr<SyntaxTree>;

    m_labelsFunction[lt::SignalProgram]         = [this](auto node) -> bool { return this->signalProgram(node); };
    m_labelsFunction[lt::Program]               = [this](auto node) -> bool { return this->program(node); };
    m_labelsFunction[lt::ProcedureIdentifier]   = [this](auto node) -> bool { return this->procedureIdentifier(node); };
    m_labelsFunction[lt::Block]                 = [this](auto node) -> bool { return this->block(node); };
    m_labelsFunction[lt::ParametersList]        = [this](auto node) -> bool { return this->parametersList(node); };
    m_labelsFunction[lt::Declarations]          = [this](auto node) -> bool { return this->declarations(node); };
    m_labelsFunction[lt::StatementsList]        = [this](auto node) -> bool { return this->statementsList(node); };
    m_labelsFunction[lt::LabelDeclarations]     = [this](auto node) -> bool { return this->labelDeclarations(node); };
    m_labelsFunction[lt::UnsignedInteger]       = [this](auto node) -> bool { return this->unsignedInteger(node); };
    m_labelsFunction[lt::LabelsList]            = [this](auto node) -> bool { return this->labelsList(node); };
    m_labelsFunction[lt::Empty]                 = [this](auto node) -> bool { return this->empty(node); };
    m_labelsFunction[lt::Identifier]            = [this](auto node) -> bool { return this->identidier(node); };
}

std::shared_ptr<SyntaxTree> Parser::analyze(std::vector<std::shared_ptr<Token>> &tokens,
                                            Tables tables,
                                            std::vector<std::string> &errors)
{
    return nullptr;
}

bool Parser::signalProgram(std::shared_ptr<SyntaxTree> node)
{
}

bool Parser::program(std::shared_ptr<SyntaxTree> node)
{
}

bool Parser::procedureIdentifier(std::shared_ptr<SyntaxTree> node)
{
}

bool Parser::block(std::shared_ptr<SyntaxTree> node)
{
}

bool Parser::parametersList(std::shared_ptr<SyntaxTree> node)
{
}

bool Parser::declarations(std::shared_ptr<SyntaxTree> node)
{
}

bool Parser::statementsList(std::shared_ptr<SyntaxTree> node)
{
}

bool Parser::labelDeclarations(std::shared_ptr<SyntaxTree> node)
{
}

bool Parser::unsignedInteger(std::shared_ptr<SyntaxTree> node)
{
}

bool Parser::labelsList(std::shared_ptr<SyntaxTree> node)
{
}

bool Parser::empty(std::shared_ptr<SyntaxTree> node)
{
}

bool Parser::identidier(std::shared_ptr<SyntaxTree> node)
{
}
