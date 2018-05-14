#include "listing.h"

Listing::Listing()
{
}

void Listing::printErrors(std::vector<std::string> errors, std::ostream &stream) const
{
    for (auto err: errors) {
        stream << err << std::endl;
    }
}

void Listing::printTokens(std::vector<std::shared_ptr<Token>> tokens, std::ostream &stream) const
{
    for (auto token: tokens) {
        stream << token->y() << "\t" << token->x() << "\t"
               << token->code() << "\t\t" << token->name() << std::endl;
    }
}

void Listing::printSyntaxTree(std::shared_ptr<SyntaxTree> node,
                              Tables tables,
                              std::ostream &stream,
                              int level) const
{
    if (node == nullptr) {
        return;
    }
    for (int i = 0; i < level; ++i) {
        stream << "..";
    }

    auto tokens = tables.tokens();
    if (node->label() == Labels::Tags::Leaf) {
        auto token = std::find_if(std::begin(tokens), std::end(tokens), [node] (auto &t) -> bool {
            return t->code() == node->code();
        });
        stream << node->code() << " " << token->get()->name() << std::endl;
    } else {
        stream << Labels::labelsList.at(node->label()) << std::endl;
    }

    ++level;
    for (auto child: node->childrens()) {
        printSyntaxTree(child, tables, stream, level);
    }
}

void Listing::printCodeText(std::string text, std::ostream &stream) const
{
    stream << text;
}
