#include <iostream>

#include "scanner.h"
#include "listing.h"

void initializeTables(std::map<std::string, int> &keywords,
                      std::map<std::string, int> &identifiers,
                      std::map<std::string, int> &constants)
{
    keywords.clear();
    identifiers.clear();
    constants.clear();

    // Scanner::TablesRange
    keywords["PROGRAM"] = 300;
    keywords["PROCEDURE"] = 301;
    keywords["BEGIN"] = 302;
    keywords["END"] = 303;
    keywords["LABEL"] = 304;
}

int main(int argc, char* argv[])
{
    std::string path_source;

    if (argc >= 2) {
        path_source = *(argv + 1);
    }

    while (path_source.empty())
    {
        std::cout << "Source filename [.sig]: ";
        std::getline(std::cin, path_source);

        if (path_source.empty()) {
            std::cout << "Line invalid, start again" << std::endl << std::endl;
        }
    }

    if (path_source.rfind(".sig") == std::string::npos) {
        path_source += ".sig";
    }

    std::ifstream fileSource(path_source);
    if (!fileSource.is_open()) {
        std::cout << "Unable to open input file: " + path_source << std::endl;
        return 0;
    }

    std::vector<std::string> errorList;
    std::map<std::string,int> keywordsTable;
    std::map<std::string,int> identifiersTable;
    std::map<std::string,int> constantsTable;
    initializeTables(keywordsTable, identifiersTable, constantsTable);

    Scanner scanner;
    Listing listing;

    auto tokens = scanner.analyze(fileSource, keywordsTable, identifiersTable, constantsTable, errorList);
    fileSource.close();

    listing.printErrors(errorList);
    listing.printTokens(tokens);

    std::cout << std::endl;

    return 0;
}
