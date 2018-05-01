#pragma once

#include <string>
#include <map>

namespace Labels {

enum class Tags : int {
    Leaf = 0,
    SignalProgram,
    Program,
    ProcedureIdentifier,
    Block,
    ParametersList,
    Declarations,
    DeclarationsList,
    StatementsList,
    LabelDeclarations,
    UnsignedInteger,
    LabelsList,
    Empty,
    Identifier
};

const std::map<Tags, std::string> labelsList = {
    { Tags::SignalProgram, "<signal-program>" },
    { Tags::Program, "<program>" },
    { Tags::ProcedureIdentifier, "<procedure-identifier>" },
    { Tags::Block, "<block>" },
    { Tags::ParametersList, "<parameters-list>" },
    { Tags::Declarations, "<declarations>" },
    { Tags::DeclarationsList, "<declarations-list>" },
    { Tags::StatementsList, "<statements-list>" },
    { Tags::LabelDeclarations, "<label-declarations>" },
    { Tags::UnsignedInteger, "<unsigned-integer>" },
    { Tags::LabelsList, "<labels-list>" },
    { Tags::Empty, "<empty>" },
    { Tags::Identifier, "<identifier>" }
};

}
