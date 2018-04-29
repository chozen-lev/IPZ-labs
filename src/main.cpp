#include <iostream>
#include <boost/program_options.hpp>

#include "tables.h"
#include "scanner.h"
#include "parser.h"
#include "listing.h"

#define VERSION "0.3.1"
#define REPOSITORY "https://github.com/chozen-lev/SIGNAL-Translator"

namespace po = boost::program_options;

int main(int argc, char* argv[])
{
    std::string path_source;

    // Declare the supported options.
    po::options_description desc("Allowed options");
    desc.add_options()
        ("version,v", "Program version")
        ("file,f", po::value<std::string>(&path_source)->default_value("test1.sig"), "Source file to be compiled")
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
    Tables tables;

    Scanner scanner;
    Parser parser;
    Listing listing;

    // Lexical analyzer
    scanner.analyze(fileStream, tables, errorList);
    fileStream.close();

    // Syntax analyzer
    auto syntaxTree = parser.analyze(tables, errorList);

    // Listing output
    outputStream << "SIGNAL translator" << std::endl;
    listing.printErrors(errorList, outputStream);
    if (vm["lexer"].as<bool>()) {
        listing.printTokens(tables.tokens(), outputStream);
    }

    outputStream << std::endl;
    listing.printSyntaxTree(syntaxTree, tables, outputStream);

    if (vm.count("output")) {
        file.close();
    }

    return 0;
}
