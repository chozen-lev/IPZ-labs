#include <iostream>
#include <cstdlib>
#include <boost/program_options.hpp>

#include "tables.h"
#include "scanner.h"
#include "parser.h"
#include "codegen.h"
#include "listing.h"

#define VERSION "0.3.9"
#define REPOSITORY "https://github.com/chozen-lev/SIGNAL-Translator"

namespace po = boost::program_options;

int main(int argc, char* argv[])
{
    std::string path_source;

    // Declare the supported options.
    po::options_description desc("Usage: csignal [options] file...\nOptions");
    desc.add_options()
        ("input-file,f", po::value<std::string>(&path_source), "Source file to be compiled.")
        ("output,o", po::value<std::string>()->implicit_value(""), "Place the output into <arg>.")
        ("lexer,l", po::value<std::string>()->implicit_value(""), "Place the tokens list into <arg>.")
        ("parser,p", po::value<std::string>()->implicit_value(""), "Place the syntax tree into <arg>.")
        ("help,h", "Display this information.")
        ("version,v", "Display compiler version information.");

    po::variables_map vm;
    try {
        po::positional_options_description p;
        p.add("input-file", -1);
        po::store(po::command_line_parser(argc, argv).options(desc).positional(p).run(), vm);
        po::notify(vm);
    } catch (const po::error &e) {
        std::cerr << "\033[1;31merror:\033[0m " << "Couldn't parse command line arguments properly:\n";
        std::cerr << e.what() << '\n' << '\n';
        std::cerr << desc << '\n';
        return EXIT_FAILURE;
    }

    if (vm.count("help")) {
        std::cout << desc << std::endl;
        return EXIT_SUCCESS;
    }
    if (vm.count("version")) {
        std::cout << "Program version " << VERSION << std::endl;
        std::cout << "GitHub repository: " << REPOSITORY << std::endl;
        return EXIT_SUCCESS;
    }
    if (path_source.empty()) {
        std::cerr << desc << std::endl;
        return EXIT_FAILURE;
    }
    std::ifstream fileStream(path_source);
    if (!fileStream.is_open()) {
        std::cerr << "\033[1;31merror:\033[0m " << path_source << ": No such file or direcory" << std::endl;
        return EXIT_FAILURE;
    }

    std::string path_file = path_source.substr(0, path_source.rfind(".") + 1);
    std::ofstream outputStream(path_file + "asm");

    std::vector<std::string> errorList;
    Tables tables;

    Scanner scanner;
    Parser parser;
    CodeGen codegen;
    Listing listing;

    scanner.analyze(fileStream, tables, errorList);
    auto syntaxTree = parser.analyze(tables, errorList);
    std::string codeText = codegen.generate(*syntaxTree, tables, errorList);

    listing.printErrors(errorList, std::cout);

    if (vm.count("output")) {
    #ifdef DEBUG
        std::cout << std::endl;
        listing.printCodeText(codeText, std::cout);
    #endif
        std::ofstream parserStream(vm["output"].as<std::string>().empty() ? path_file + "asm" : vm["output"].as<std::string>());
        listing.printCodeText(codeText, parserStream);
        parserStream.close();
    }
    if (vm.count("lexer")) {
    #ifdef DEBUG
        std::cout << std::endl;
        listing.printTokens(tables.tokens(), std::cout);
    #endif
        std::ofstream lexerStream(vm["lexer"].as<std::string>().empty() ? path_file + "lexer" : vm["lexer"].as<std::string>());
        listing.printTokens(tables.tokens(), lexerStream);
        lexerStream.close();
    }
    if (vm.count("parser")) {
    #ifdef DEBUG
        std::cout << std::endl;
        listing.printSyntaxTree(syntaxTree, tables, std::cout);
    #endif
        std::ofstream parserStream(vm["parser"].as<std::string>().empty() ? path_file + "parser" : vm["parser"].as<std::string>());
        listing.printSyntaxTree(syntaxTree, tables, parserStream);
        parserStream.close();
    }

    outputStream.close();

    return errorList.empty() ? EXIT_SUCCESS : EXIT_FAILURE;
}
