#include "parser.h"

Parser::Parser()
{
}

std::shared_ptr<SyntaxTree> Parser::analyze(Tables &tables, std::vector<std::string> &errors)
{
    std::shared_ptr<SyntaxTree> tree;

    auto tokens = tables.tokens();
    auto begin = std::begin(tokens);
    auto end = std::end(tokens);

    signalProgram(tree, begin, end, tables, errors);

    return tree;
}

bool Parser::signalProgram(auto &node, auto &token, auto end, auto &tables, auto &errors)
{
    node = std::make_shared<SyntaxTree>(Labels::Tags::SignalProgram);
    if (!program(node, token, end, tables, errors)) {
        return false;
    }
    return true;
}

bool Parser::program(auto &node, auto &token, auto end, auto &tables, auto &errors)
{
    auto child = node->addChild(Labels::Tags::Program);

    if (leaf(child, token, end, tables, errors, PROGRAM_CODE, Tables::Range::keywordsBegin, true)) {
        if (!procedureIdentifier(child, token, end, tables, errors)) {
            return false;
        }

        if (!leaf(child, token, end, tables, errors, ';', static_cast<Tables::Range>(0), true)) {
            return false;
        }

        if (!block(child, token, end, tables, errors)) {
            return false;
        }

        if (!leaf(child, token, end, tables, errors, '.', static_cast<Tables::Range>(0), true)) {
            return false;
        }

        return true;
    }

    if (leaf(child, token, end, tables, errors, PROCEDURE_CODE, Tables::Range::keywordsBegin, true)) {
        if (!procedureIdentifier(child, token, end, tables, errors)) {
            return false;
        }

        if (!parametersList(child, token, end, tables, errors)) {
            return false;
        }

        if (!leaf(child, token, end, tables, errors, ';', static_cast<Tables::Range>(0), true)) {
            return false;
        }

        if (!block(child, token, end, tables, errors)) {
            return false;
        }

        if (!leaf(child, token, end, tables, errors, ';', static_cast<Tables::Range>(0), true)) {
            return false;
        }

        return true;
    }

    return false;
}

bool Parser::procedureIdentifier(auto &node, auto &token, auto end, auto &tables, auto &errors)
{
    auto child = node->addChild(Labels::Tags::ProcedureIdentifier);
    if (!identidier(child, token, end, tables, errors)) {
        return false;
    }
    return true;
}

bool Parser::block(auto &node, auto &token, auto end, auto &tables, auto &errors)
{
    auto child = node->addChild(Labels::Tags::Block);

    if (!declarations(child, token, end, tables, errors)) {
        return false;
    }

    if (!leaf(child, token, end, tables, errors, BEGIN_CODE, Tables::Range::keywordsBegin, true)) {
        return false;
    }

    if (!statementsList(child, token, end, tables, errors)) {
        return false;
    }

    if (!leaf(child, token, end, tables, errors, END_CODE, Tables::Range::keywordsBegin, true)) {
        return false;
    }

    return true;
}

bool Parser::parametersList(auto &node, auto &token, auto end, auto &tables, auto &errors)
{
    auto child = node->addChild(Labels::Tags::Block);

    if (!leaf(child, token, end, tables, errors, static_cast<int>('('), static_cast<Tables::Range>(0), false)) {
        child->addChild(Labels::Tags::Empty);
        return true;
    }

    if (!declarationsList(child, token, end, tables, errors)) {
        return false;
    }

    if (!leaf(child, token, end, tables, errors, static_cast<int>(')'), static_cast<Tables::Range>(0), true)) {
        return false;
    }

    return true;
}

bool Parser::declarations(auto &node, auto &token, auto end, auto &tables, auto &errors)
{
    auto child = node->addChild(Labels::Tags::Declarations);
    if (!labelDeclarations(child, token, end, tables, errors)) {
        return false;
    }
    return true;
}

bool Parser::declarationsList(auto &node, auto &token, auto end, auto &tables, auto &errors)
{
    auto child = node->addChild(Labels::Tags::DeclarationsList);
    child->addChild(Labels::Tags::Empty);
    return true;
}

bool Parser::statementsList(auto &node, auto &token, auto end, auto &tables, auto &errors)
{
    auto child = node->addChild(Labels::Tags::StatementsList);
    child->addChild(Labels::Tags::Empty);
    return true;
}

bool Parser::labelDeclarations(auto &node, auto &token, auto end, auto &tables, auto &errors)
{
    auto child = node->addChild(Labels::Tags::LabelDeclarations);

    if (!leaf(child, token, end, tables, errors, LABEL_CODE, Tables::Range::keywordsBegin, false)) {
        child->addChild(Labels::Tags::Empty);
        return true;
    }

    if (!unsignedInteger(child, token, end, tables, errors)) {
        return false;
    }

    if (!labelsList(child, token, end, tables, errors)) {
        return false;
    }

    if (!leaf(child, token, end, tables, errors, ';', static_cast<Tables::Range>(0), true)) {
        return false;
    }

    return true;
}

bool Parser::unsignedInteger(auto &node, auto &token, auto end, auto &tables, auto &errors)
{
    auto child = node->addChild(Labels::Tags::UnsignedInteger);
    if (!leaf(child, token, end, tables, errors, token->get()->code(), Tables::Range::constantsBegin, true)) {
        return false;
    }
    return true;
}

bool Parser::labelsList(auto &node, auto &token, auto end, auto &tables, auto &errors)
{
    auto child = node->addChild(Labels::Tags::LabelsList);

    if (!leaf(child, token, end, tables, errors, ',', static_cast<Tables::Range>(0), false)) {
        child->addChild(Labels::Tags::Empty);
        return true;
    }

    if (!unsignedInteger(child, token, end, tables, errors)) {
        return false;
    }

    if (!labelsList(child, token, end, tables, errors)) {
        return false;
    }

    return true;
}

bool Parser::identidier(auto &node, auto &token, auto end, auto &tables, auto &errors)
{
    auto child = node->addChild(Labels::Tags::Identifier);
    if (!leaf(child, token, end, tables, errors, token->get()->code(), Tables::Range::identifiersBegin, true)) {
        return false;
    }
    return true;
}

bool Parser::leaf(auto &node, auto &token, auto end, auto &tables, auto &errors, int code, Tables::Range range, bool required)
{
    if (token == end) {
        errors.push_back("Parser: Error: '.' expected but EOF found");
        return false;
    }
    if (range != static_cast<Tables::Range>(0) && (tables.getRange(token->get()->code()) != range || token->get()->code() != code)) {
        std::string buff;
        switch (range) {
        case Tables::Range::keywordsBegin:
            buff = "Keyword";
            break;
        case Tables::Range::constantsBegin:
            buff = "Constant";
            break;
        case Tables::Range::identifiersBegin:
            buff = "Identifier";
            break;
        }
        errors.push_back("Parser: Error (line: " + std::to_string((token)->get()->y())
                          + ", column: " + std::to_string(token->get()->x()) + "): "
                          + buff + " '" + tables.name(code)
                          + "' expected but '" + token->get()->name() + "' found");
        return false;
    }
    if (code != -1 && token->get()->code() != code) {
        if (!required) {
            return false;
        }
        errors.push_back("Parser: Error (line: "
                         + std::to_string((token)->get()->y())
                         + ", column: "
                         + std::to_string(token->get()->x())
                         + "): " + "'" + char(code)
                         + "' expected but '" + token->get()->name() + "' found");
        return false;
    }
    node->addChild(token->get()->code());
    ++token;
    return true;
}
