#include "lexicalanalyzer.h"

#include <iostream>

LexicalAnalyzer::LexicalAnalyzer(std::map<std::string, int> *keyword, std::map<std::string, int> *identifier, std::map<std::string, int> *constant)
    : keywordsTable(keyword),
      identifiersTable(identifier),
      constantsTable(constant)
{

}

std::vector<Token*> LexicalAnalyzer::analyze(std::ifstream &stream)
{
    std::vector<Token*> lexOutput;
    int x = 1, y = 1;

    Symbol symbol;
    std::string buff;
    int lexCode;
    bool SuppressOutput = false;

    symbol = gets(stream);

    while (!stream.eof()) {
        buff.clear();
        lexCode = 0;
        SuppressOutput = false;

        switch ((int)symbol.attr) {
        case Whitespace: {
            while (!stream.eof() && symbol.attr == Whitespace) {
                if (symbol.value == '\n') {
                    x = 1;
                    y++;
                } else { x++; }

                symbol = gets(stream);
            }
            SuppressOutput = true;
            break;
        }
        case Constant: {
            while (!stream.eof() && symbol.attr == Constant) {
                buff += symbol.value;
                symbol = gets(stream);
            }
            if (search(constantsTable, buff) >= 0) {
                lexCode = constantsTable->at(buff);
            } else {
                lexCode = append(constantsTable, constantsBegin, buff);
            }
            break;
        }
        case Identifier: {
            while (!stream.eof() && (symbol.attr == Identifier || symbol.attr == Constant)) {
                buff += symbol.value;
                symbol = gets(stream);
            }
            if (search(keywordsTable, buff) >= 0) {
                lexCode = keywordsTable->at(buff);
            } else if (search(identifiersTable, buff) >= 0) {
                lexCode = identifiersTable->at(buff);
            } else {
                lexCode = append(keywordsTable, keywordsBegin, buff);
            }
            break;
        }
        case Comment: {
            if (stream.eof()) {
                lexCode = symbol.value;
                buff += symbol.value;
            } else {
                symbol = gets(stream);
                if (symbol.value == '*') {
                    int x1 = x + 1, y1 = y;

                    if (stream.eof()) {
                        std::cout << "Lexer: Error (line " << y << ", column " << x << "): *) expected but end of file found" << std::endl;
                        SuppressOutput = true;
                        break;
                    }

                    symbol = gets(stream);
                    x1++;

                    do {
                        while (!stream.eof() && (symbol.value != '*' || symbol.attr == Whitespace)) {
                            if (symbol.value == '\n') {
                                x1 = 1;
                                y1++;
                            } else { x1++; }

                            symbol = gets(stream);
                        }
                        if (stream.eof()) {
                            std::cout << "Lexer: Error (line " << y << ", column " << x << "): *) expected but end of file found" << std::endl;
                            SuppressOutput = true;
                            break;
                        }

                        x1++;
                        symbol = gets(stream);
                    } while (symbol.value != ')');

                    if (symbol.value == ')') {
                        x = x1 + 1;
                        y = y1;
                        SuppressOutput = true;
                    }
                } else {
                    lexOutput.push_back(new Token({ "(", '(', x++, y }));
                    buff += symbol.value;
                    lexCode = symbol.value;
                }
                if (!stream.eof()) {
                    symbol = gets(stream);
                }
            }
            break;
        }
        case Separator: {
            lexCode = symbol.value;
            buff += symbol.value;
            symbol = gets(stream);
            break;
        }
        case Invalid: {
            symbol = gets(stream);
            break;
        }
        }
        if (!SuppressOutput) {
            lexOutput.push_back(new Token({ buff, lexCode, x, y }));
            x += buff.size();
        }
    }

    return lexOutput;
}

LexicalAnalyzer::Symbol LexicalAnalyzer::gets(std::ifstream &stream)
{
    Symbol symbol;
    stream.get(symbol.value);
    symbol.attr = (Attributes)attributes[(int)symbol.value];

    return symbol;
}

int LexicalAnalyzer::search(std::map<std::string,int> *table, std::string &token)
{
    if (table->find(token) == table->end()) {
        return -1;
    }
    return table->at(token);
}

int LexicalAnalyzer::append(std::map<std::string,int> *table, int RangeBegin, std::string token)
{
    if (search(table, token) >= 0) {
        return table->at(token);
    }
    table->insert(std::pair<std::string,int>(token, RangeBegin + table->size()));
    return table->at(token);
}
