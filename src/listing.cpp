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
