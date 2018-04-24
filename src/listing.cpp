#include "listing.h"

Listing::Listing()
{

}

void Listing::printErrors(std::vector<std::string> errors, std::ostream &stream)
{
    for (auto err: errors) {
        stream << err << std::endl;
    }
}

void Listing::printTokens(std::vector<std::shared_ptr<Token>> tokens, std::ostream &stream)
{
    for (auto token: tokens) {
        stream << token->y() << "\t" << token->x() << "\t"
               << token->code() << "\t\t" << token->name() << std::endl;
    }
}

void Listing::printSyntaxTree(std::shared_ptr<SyntaxTree> node,
                              Tables tables,
                              std::vector<std::shared_ptr<Token>> tokens,
                              std::ostream &stream,
                              int level)
{
    if (node == nullptr) {
        return;
    }
    for (int i = 0; i < level; ++i) {
        stream << "..";
    }

    if (node->label() == Labels::Tags::Leaf) {
        auto table = tables.table(node->code());
        auto token = std::find_if(std::begin(tokens), std::end(tokens), [node] (auto &t) -> bool {
            return t->code() == node->code();
        });
        stream << node->code() << " " << token->get()->name() << std::endl;
    } else {
        stream << Labels::labelsList.at(node->label()) << std::endl;
    }

    for (auto child: node->childrens()) {
        printSyntaxTree(child, tables, tokens, stream, ++level);
    }
}
