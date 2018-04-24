#include "tables.h"

Tables::Tables()
{
    // Scanner::TablesRange
    m_keywords["PROGRAM"] = 300;
    m_keywords["PROCEDURE"] = 301;
    m_keywords["BEGIN"] = 302;
    m_keywords["END"] = 303;
    m_keywords["LABEL"] = 304;
}

int Tables::search(Range rangeBegin, std::string &token) const
{
    auto tb = m_constants;
    if (tb.find(token) == std::end(tb)) {
        return -1;
    }
    return tb.at(token);
}

int Tables::append(Tables::Range rangeBegin, std::string &token)
{
    auto tb = m_constants;
    if (search(rangeBegin, token) >= 0) {
        return tb.at(token);
    }
    tb.insert(std::pair<std::string, int>(token, static_cast<int>(rangeBegin) + tb.size()));
    return tb.at(token);
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
    auto rcode = static_cast<Range>(code);

    if (rcode >= Range::keywordsBegin && code < m_keywords.size()) {
        return m_keywords;
    }
    if (rcode >= Range::identifiersBegin && code < m_identifiers.size()) {
        return m_identifiers;
    }
    if (rcode >= Range::constantsBegin && code < m_constants.size()) {
        return m_constants;
    }
    throw std::runtime_error("Invalid token code! There is any token with such code.");
}
