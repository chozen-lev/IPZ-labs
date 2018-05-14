#include "tables.h"

Tables::Tables()
{
    // Tables::Range
    m_keywords["PROGRAM"] = PROGRAM_CODE;
    m_keywords["PROCEDURE"] = PROCEDURE_CODE;
    m_keywords["BEGIN"] = BEGIN_CODE;
    m_keywords["END"] = END_CODE;
    m_keywords["LABEL"] = LABEL_CODE;
}

int Tables::search(Range rangeBegin, std::string name)
{
    std::map<std::string, int> &table = this->table(rangeBegin);
    if (table.find(name) == std::end(table)) {
        return -1;
    }
    return table.at(name);
}

int Tables::append(Tables::Range rangeBegin, std::string name)
{
    std::map<std::string, int> &table = this->table(rangeBegin);
    if (search(rangeBegin, name) >= 0) {
        return table.at(name);
    }
    table.insert(std::pair<std::string, int>(name, static_cast<int>(rangeBegin) + table.size()));
    return table.at(name);
}

std::map<std::string, int> &Tables::table(Tables::Range rangeBegin)
{
    switch (rangeBegin) {
    case Range::keywordsBegin:
        return m_keywords;
    case Range::identifiersBegin:
        return m_identifiers;
    case Range::constantsBegin:
        return m_constants;
    default:
        throw std::runtime_error("Invalid range type!");
    }
}

std::map<std::string, int> &Tables::table(int code)
{
    auto range = getRange(code);
    return table(range);
}

std::string Tables::name(int code)
{
    if (code > 0 && code < static_cast<int>(Range::keywordsBegin)) {
        return std::string(1, static_cast<char>(code));
    }

    std::map<std::string, int> table = this->table(getRange(code));

    auto it = std::find_if(std::begin(table), std::end(table),
                              [code](const auto& t) -> bool {
                                  return t.second == code;
                              }
                          );
    return it->first;
}

void Tables::addToken(Token token)
{
    m_tokens.push_back(std::make_shared<Token>(token));
}

std::vector<std::shared_ptr<Token>> &Tables::tokens()
{
    return m_tokens;
}

Tables::Range Tables::getRange(int code) const
{
    int keywordsBegin = static_cast<int>(Range::keywordsBegin);
    int identifiersBegin = static_cast<int>(Range::identifiersBegin);
    int constantsBegin = static_cast<int>(Range::constantsBegin);

    if (code >= keywordsBegin && code < keywordsBegin + m_keywords.size()) {
        return Range::keywordsBegin;
    }
    if (code >= identifiersBegin && code < identifiersBegin + m_identifiers.size()) {
        return Range::identifiersBegin;
    }
    if (code >= constantsBegin && code < constantsBegin + m_constants.size()) {
        return Range::constantsBegin;
    }
    throw std::runtime_error("Invalid token code! There is any token with such code.");
}
