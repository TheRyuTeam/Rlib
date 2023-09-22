#include <foundation/UriQuery.h>
#include <foundation/StringUtils.h>
#include <foundation/Exception.h>

RLIB_START

UriQuery::UriQuery(const std::string& query)
    : UriQuery(query.begin(), query.end())
{
}

UriQuery::UriQuery(const std::string::const_iterator& begin, const std::string::const_iterator& end)
    : _queries()
{
    parse(begin, end);
}

bool UriQuery::has(const std::string& key) const
{
    return _queries.find(key) != _queries.end();
}

std::string UriQuery::operator[](const std::string& key) const
{
    auto it = _queries.find(key);
    if (it == _queries.end()) {
        return "";
    }

    return it->second;
}

std::string& UriQuery::operator[](const std::string& key)
{
    return _queries[key];
}

std::string UriQuery::toString() const
{
    std::string str;
    if (!_queries.empty()) {
        str += '?';
        auto it = std::begin(_queries);
        auto next = std::next(it);
        const auto end = std::end(_queries);

        if (it != end) {
            while (next != end) {
                str += it->first + '=' + it->second + '&';
                ++it;
                ++next;
            }

            str += it->first + '=' + it->second;
        }
    }

    return str;
}

std::string::const_iterator UriQuery::parse(std::string::const_iterator it, const std::string::const_iterator& end)
{
    if (it == end) {
        return it;
    }

    if (*it != '?') {
        throw ParseError("Expected '?' at query start");
    }
    ++it;
    while (it != end) {
        auto begin = exchange(it, readUntilWithForbidden(it, end, '=', kForbiddenSymbols, "Uri query can not contain"));
        if (it == end) {
            throw ParseError("Expected '=' after uri query key");
        }

        std::string key(begin, it++);

        begin = exchange(it, readUntilWithForbidden(it, end, '&', kForbiddenSymbols, "Uri query can not contain"));
        std::string value(begin, it);
        _queries[key] = value;
        if (it == end) {
            return it;
        }
        ++it;
    }

    return it;
}

RLIB_END
