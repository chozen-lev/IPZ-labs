#include "parser.h"

Parser::Parser()
{
    using lt = Labels::Tags;
    using shared_tree = std::shared_ptr<SyntaxTree>;

    m_labelsFunction[lt::SignalProgram]         = [this](shared_tree node) -> void { this->signalProgram(node); };
    m_labelsFunction[lt::Program]               = [this](shared_tree node) -> void { this->program(node); };
    m_labelsFunction[lt::ProcedureIdentifier]   = [this](shared_tree node) -> void { this->procedureIdentifier(node); };
    m_labelsFunction[lt::Block]                 = [this](shared_tree node) -> void { this->block(node); };
    m_labelsFunction[lt::ParametersList]        = [this](shared_tree node) -> void { this->parametersList(node); };
    m_labelsFunction[lt::Declarations]          = [this](shared_tree node) -> void { this->declarations(node); };
    m_labelsFunction[lt::StatementsList]        = [this](shared_tree node) -> void { this->statementsList(node); };
    m_labelsFunction[lt::LabelDeclarations]     = [this](shared_tree node) -> void { this->labelDeclarations(node); };
    m_labelsFunction[lt::UnsignedInteger]       = [this](shared_tree node) -> void { this->unsignedInteger(node); };
    m_labelsFunction[lt::LabelsList]            = [this](shared_tree node) -> void { this->labelsList(node); };
    m_labelsFunction[lt::Empty]                 = [this](shared_tree node) -> void { this->empty(node); };
    m_labelsFunction[lt::Identifier]            = [this](shared_tree node) -> void { this->identidier(node); };
}

std::shared_ptr<SyntaxTree> Parser::analyze(std::vector<std::shared_ptr<Token>> &tokens,
                                            std::map<std::string, int> &keywords,
                                            std::map<std::string, int> &identifiers,
                                            std::map<std::string, int> &constans,
                                            std::vector<std::string> &errors)
{
    auto begin = std::begin(tokens);
    auto end = std::end(tokens);

    return nullptr;
}

void Parser::signalProgram(std::shared_ptr<SyntaxTree> node)
{

}

void Parser::program(std::shared_ptr<SyntaxTree> node)
{

}

void Parser::procedureIdentifier(std::shared_ptr<SyntaxTree> node)
{

}

void Parser::block(std::shared_ptr<SyntaxTree> node)
{

}

void Parser::parametersList(std::shared_ptr<SyntaxTree> node)
{

}

void Parser::declarations(std::shared_ptr<SyntaxTree> node)
{

}

void Parser::statementsList(std::shared_ptr<SyntaxTree> node)
{

}

void Parser::labelDeclarations(std::shared_ptr<SyntaxTree> node)
{

}

void Parser::unsignedInteger(std::shared_ptr<SyntaxTree> node)
{

}

void Parser::labelsList(std::shared_ptr<SyntaxTree> node)
{

}

void Parser::empty(std::shared_ptr<SyntaxTree> node)
{

}

void Parser::identidier(std::shared_ptr<SyntaxTree> node)
{

}
