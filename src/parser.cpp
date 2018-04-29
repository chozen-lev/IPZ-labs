#include "parser.h"

#define Q_UNUSED(x) (void)x;

Parser::Parser()
{
}

std::shared_ptr<SyntaxTree> Parser::analyze(Tables &tables, std::vector<std::string> &errors)
{
    auto tree = std::make_shared<SyntaxTree>();

    auto builder = Builder(tree, tables);
    auto tokens = TokenIterator(tables.tokens());

    signalProgram(builder, tokens, errors);

    return tree;
}

bool Parser::signalProgram(Builder builder, TokenIterator &tokens, std::vector<std::string> &errors)
{
    builder.node->setLabel(Labels::Tags::SignalProgram);
    if (!program(builder, tokens, errors)) {
        return false;
    }
    return true;
}

bool Parser::program(Builder builder, TokenIterator &tokens, std::vector<std::string> &errors)
{
    builder.node = builder.node->addChild(Labels::Tags::Program);

    if (leaf(builder, tokens, errors, PROGRAM_CODE, Tables::Range::keywordsBegin)) {
        if (!procedureIdentifier(builder, tokens, errors)) {
            return false;
        }

        if (!leaf(builder, tokens, errors, ';')) {
            return false;
        }

        if (!block(builder, tokens, errors)) {
            return false;
        }

        if (!leaf(builder, tokens, errors, '.')) {
            return false;
        }

        return true;
    }

    if (leaf(builder, tokens, errors, PROCEDURE_CODE, Tables::Range::keywordsBegin)) {
        if (!procedureIdentifier(builder, tokens, errors)) {
            return false;
        }

        if (!parametersList(builder, tokens, errors)) {
            return false;
        }

        if (!leaf(builder, tokens, errors, ';')) {
            return false;
        }

        if (!block(builder, tokens, errors)) {
            return false;
        }

        if (!leaf(builder, tokens, errors, ';')) {
            return false;
        }

        return true;
    }

    return false;
}

bool Parser::procedureIdentifier(Builder builder, TokenIterator &tokens, std::vector<std::string> &errors)
{
    builder.node = builder.node->addChild(Labels::Tags::ProcedureIdentifier);
    if (!identidier(builder, tokens, errors)) {
        return false;
    }
    return true;
}

bool Parser::block(Builder builder, TokenIterator &tokens, std::vector<std::string> &errors)
{
    builder.node = builder.node->addChild(Labels::Tags::Block);

    if (!declarations(builder, tokens, errors)) {
        return false;
    }

    if (!leaf(builder, tokens, errors, BEGIN_CODE, Tables::Range::keywordsBegin)) {
        return false;
    }

    if (!statementsList(builder, tokens, errors)) {
        return false;
    }

    if (!leaf(builder, tokens, errors, END_CODE, Tables::Range::keywordsBegin)) {
        return false;
    }

    return true;
}

bool Parser::parametersList(Builder builder, TokenIterator &tokens, std::vector<std::string> &errors)
{
    builder.node = builder.node->addChild(Labels::Tags::Block);

    if (!leaf(builder, tokens, errors, static_cast<int>('('), static_cast<Tables::Range>(0), false)) {
        builder.node->addChild(Labels::Tags::Empty);
        return true;
    }

    if (!declarationsList(builder, tokens, errors)) {
        return false;
    }

    if (!leaf(builder, tokens, errors, static_cast<int>(')'))) {
        return false;
    }

    return true;
}

bool Parser::declarations(Builder builder, TokenIterator &tokens, std::vector<std::string> &errors)
{
    builder.node = builder.node->addChild(Labels::Tags::Declarations);
    if (!labelDeclarations(builder, tokens, errors)) {
        return false;
    }
    return true;
}

bool Parser::declarationsList(Builder builder, TokenIterator &tokens, std::vector<std::string> &errors)
{
    Q_UNUSED(tokens)
    builder.node = builder.node->addChild(Labels::Tags::DeclarationsList);
    builder.node->addChild(Labels::Tags::Empty);
    return true;
}

bool Parser::statementsList(Builder builder, TokenIterator &tokens, std::vector<std::string> &errors)
{
    Q_UNUSED(tokens)
    builder.node = builder.node->addChild(Labels::Tags::StatementsList);
    builder.node->addChild(Labels::Tags::Empty);
    return true;
}

bool Parser::labelDeclarations(Builder builder, TokenIterator &tokens, std::vector<std::string> &errors)
{
    builder.node = builder.node->addChild(Labels::Tags::LabelDeclarations);

    if (!leaf(builder, tokens, errors, LABEL_CODE, Tables::Range::keywordsBegin, false)) {
        builder.node->addChild(Labels::Tags::Empty);
        return true;
    }

    if (!unsignedInteger(builder, tokens, errors)) {
        return false;
    }

    if (!labelsList(builder, tokens, errors)) {
        return false;
    }

    if (!leaf(builder, tokens, errors, ';')) {
        return false;
    }

    return true;
}

bool Parser::unsignedInteger(Builder builder, TokenIterator &tokens, std::vector<std::string> &errors)
{
    builder.node = builder.node->addChild(Labels::Tags::UnsignedInteger);
    if (!leaf(builder, tokens, errors, tokens.token->get()->code(), Tables::Range::constantsBegin)) {
        return false;
    }
    return true;
}

bool Parser::labelsList(Builder builder, TokenIterator &tokens, std::vector<std::string> &errors)
{
    builder.node = builder.node->addChild(Labels::Tags::LabelsList);

    if (!leaf(builder, tokens, errors, ',', static_cast<Tables::Range>(0), false)) {
        builder.node->addChild(Labels::Tags::Empty);
        return true;
    }

    if (!unsignedInteger(builder, tokens, errors)) {
        return false;
    }

    if (!labelsList(builder, tokens, errors)) {
        return false;
    }

    return true;
}

bool Parser::identidier(Builder builder, TokenIterator &tokens, std::vector<std::string> &errors)
{
    builder.node = builder.node->addChild(Labels::Tags::Identifier);
    if (!leaf(builder, tokens, errors, tokens.token->get()->code(), Tables::Range::identifiersBegin)) {
        return false;
    }
    return true;
}

bool Parser::leaf(Builder builder, TokenIterator &tokens, std::vector<std::string> &errors, int code, Tables::Range range, bool required)
{
    if (tokens.token == tokens.end) {
        errors.push_back("Parser: Error: '.' expected but EOF found");
        return false;
    }

    auto token = *tokens.token->get();
    if (range != static_cast<Tables::Range>(0) && (builder.tables.getRange(token.code()) != range || token.code() != code)) {
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
        errors.push_back("Parser: Error (line: " + std::to_string(token.y())
                          + ", column: " + std::to_string(token.x()) + "): "
                          + buff + " '" + builder.tables.name(code)
                          + "' expected but '" + token.name() + "' found");
        return false;
    }

    if (code != -1 && token.code() != code) {
        if (!required) {
            return false;
        }
        errors.push_back("Parser: Error (line: " + std::to_string(token.y())
                         + ", column: " + std::to_string(token.x())
                         + "): " + "'" + char(code) + "' expected but '"
                         + token.name() + "' found");
        return false;
    }

    builder.node->addChild(token.code());
    ++tokens.token;

    return true;
}
