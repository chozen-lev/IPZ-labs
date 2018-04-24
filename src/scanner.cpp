#include "scanner.h"

Scanner::Scanner()
{
}

std::vector<std::shared_ptr<Token>> Scanner::analyze(std::ifstream &stream, Tables tables, std::vector<std::string> &errors)
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
            if (tables.search(Tables::Range::constantsBegin, buff) >= 0) {
                lexCode = tables.table(Tables::Range::constantsBegin).at(buff);
            } else {
                lexCode = tables.append(Tables::Range::constantsBegin, buff);
            }
            break;
        case Identifier:
            while (!stream.eof() && (symbol.attr == Identifier || symbol.attr == Constant)) {
                buff += symbol.value;
                symbol.gets(stream);
            }

            if (tables.search(Tables::Range::keywordsBegin, buff) >= 0) {
                lexCode = tables.table(Tables::Range::keywordsBegin).at(buff);
            } else if (tables.search(Tables::Range::identifiersBegin, buff) >= 0) {
                lexCode = tables.table(Tables::Range::identifiersBegin).at(buff);
            } else {
                lexCode = tables.append(Tables::Range::identifiersBegin, buff);
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
