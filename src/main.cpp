#include <iostream>
#include <boost/program_options.hpp>

#include "scanner.h"
#include "parser.h"
#include "listing.h"

#define VERSION "0.3.1"
#define REPOSITORY "https://github.com/chozen-lev/SIGNAL-Translator"

namespace po = boost::program_options;

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

    // Declare the supported options.
    po::options_description desc("Allowed options");
    desc.add_options()
        ("version,v", "Program version")
        ("file,f", po::value<std::string>(&path_source), "Source file to be compiled")
        ("output,o", po::value<std::string>(), "Name of output file")
        ("lexer,l", po::bool_switch()->default_value(false), "Wheater dump lexer result or not.")
        ("help,h", "Produce help message");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("version")) {
        std::cerr << "Program version " << VERSION << std::endl << std::endl;
        std::cerr << "GitHub repository: " << REPOSITORY << std::endl;
        return 1;
    }
    if (vm.count("help") || vm.count("file") == 0) {
        std::cerr << desc << std::endl;
        return 1;
    }

    std::ifstream fileStream(path_source);
    if (!fileStream.is_open()) {
        std::cerr << "Unable to open input file: " + path_source << std::endl;
        return 1;
    }

    std::streambuf *buff = std::cout.rdbuf();
    std::ofstream file;
    if (vm.count("output")) {
        file.open(vm["output"].as<std::string>());
        buff = file.rdbuf();
    }
    std::ostream outputStream(buff);

    std::vector<std::string> errorList;
    std::map<std::string, int> keywordsTable;
    std::map<std::string, int> identifiersTable;
    std::map<std::string, int> constantsTable;
    initializeTables(keywordsTable, identifiersTable, constantsTable);

    Scanner scanner;
    Parser parser;
    Listing listing;

    // Lexical analyzer
    auto tokens = scanner.analyze(fileStream, keywordsTable, identifiersTable, constantsTable, errorList);
    fileStream.close();

    // Syntax analyzer
    auto syntaxTree = parser.analyze(tokens, keywordsTable, identifiersTable, constantsTable, errorList);

    // Listing output
    outputStream << "SIGNAL translator" << std::endl;
    listing.printErrors(errorList, outputStream);
    if (vm["lexer"].as<bool>()) {
        listing.printTokens(tokens, outputStream);
    }

    if (vm.count("output")) {
        file.close();
    }

    return 0;
}
