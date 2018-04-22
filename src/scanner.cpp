#include "scanner.h"

Scanner::Scanner()
{
}

std::vector<std::shared_ptr<Token>> Scanner::analyze(std::ifstream &stream,
                                                     std::map<std::string, int> &keywords,
                                                     std::map<std::string, int> &identifiers,
                                                     std::map<std::string, int> &constans,
                                                     std::vector<std::string> &errors)
{
    std::vector<std::shared_ptr<Token>> tokens;

    Symbol symbol;
    int x = 1, y = 1;
    std::string buff;
    int lexCode;
    bool suppressOutput;

    symbol.gets(stream);
    while (!stream.eof()) {
        buff.clear();
        lexCode = 0;
        suppressOutput = false;

        switch (static_cast<int>(symbol.attr)) {
        case Whitespace:
            while (!stream.eof() && symbol.attr == Whitespace) {
                if (symbol.value == '\n') {
                    x = 1;
                    y++;
                } else { x++; }
                symbol.gets(stream);
            }
            suppressOutput = true;
            break;
        case Constant:
            while (!stream.eof() && symbol.attr == Constant) {
                buff += symbol.value;
                symbol.gets(stream);
            }
            if (search(constans, buff) >= 0) {
                lexCode = constans.at(buff);
            } else {
                lexCode = append(constans, TablesRange::constantsBegin, buff);
            }
            break;
        case Identifier:
            while (!stream.eof() && (symbol.attr == Identifier || symbol.attr == Constant)) {
                buff += symbol.value;
                symbol.gets(stream);
            }

            if (search(keywords, buff) >= 0) {
                lexCode = keywords.at(buff);
            } else if (search(identifiers, buff) >= 0) {
                lexCode = identifiers.at(buff);
            } else {
                lexCode = append(identifiers, TablesRange::identifiersBegin, buff);
            }
            break;
        case Separator:
            lexCode = symbol.value;
            buff += symbol.value;
            symbol.gets(stream);
            break;
        case Comment:
            if (stream.eof()) {
                lexCode = symbol.value;
                buff += symbol.value;
                break;
            }

            symbol.gets(stream);
            if (symbol.value == '*') {
                int x1 = ++x, y1 = y;

                if (stream.eof()) {
                    suppressOutput = true;
                    errors.push_back("Lexer: Error (line " + std::to_string(y1)
                                     + ", column " + std::to_string(x1)
                                     + "): *) expected but end of file found");
                    break;
                }

                x++;
                symbol.gets(stream);
                do
                {
                    while (!stream.eof() && (symbol.value != '*' || symbol.attr == Whitespace)) {
                        if (symbol.value == '\n') {
                            x = 1;
                            y++;
                        } else { x++; }
                        symbol.gets(stream);
                    }
                    if (stream.eof()) {
                        suppressOutput = true;
                        errors.push_back("Lexer: Error (line " + std::to_string(y1)
                                         + ", column " + std::to_string(x1)
                                         + "): *) expected but end of file found");
                        break;
                    }

                    x++;
                    symbol.gets(stream);
                } while (symbol.value != ')');

                if (symbol.value == ')') {
                    x++;
                    suppressOutput = true;
                }
            } else {
                tokens.push_back(std::make_shared<Token>(Token { "(", '(', { x++, y } }));
                buff += symbol.value;
                lexCode = symbol.value;
            }
            if (!stream.eof()) {
                symbol.gets(stream);
            }
            break;
        default:
            while (!stream.eof() && symbol.attr == Invalid) {
                buff += symbol.value;
                symbol.gets(stream);
            }
            suppressOutput = true;
            errors.push_back("Lexer: Error (line " + std::to_string(y)
                             + ", column " + std::to_string(x)
                             + "): invalid character");
            break;
        }
        if (!suppressOutput) {
            tokens.push_back(std::make_shared<Token>(Token { buff, lexCode, { x, y } }));
        }
        x += buff.size();
    }

    return tokens;
}

int Scanner::search(std::map<std::string, int> &table, std::string &token)
{
    if (table.find(token) == std::end(table)) {
        return -1;
    }
    return table.at(token);
}

int Scanner::append(std::map<std::string, int> &table, TablesRange rangeBegin, std::string &token)
{
    if (search(table, token) >= 0) {
        return table.at(token);
    }
    table.insert(std::pair<std::string, int>(token, static_cast<int>(rangeBegin) + table.size()));
    return table.at(token);
}

void Scanner::Symbol::gets(std::ifstream &stream)
{
    stream.get(value);
    int code = static_cast<int>(value);
    if (code >= 0 && code < ASCII_SIZE) {
        attr = asciiAttr[static_cast<int>(value)];
    } else {
        attr = Invalid;
    }
}
