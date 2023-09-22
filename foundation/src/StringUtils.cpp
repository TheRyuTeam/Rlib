#include <foundation/StringUtils.h>
#include <foundation/Exception.h>

RLIB_START

std::size_t skipWs(const std::string& str, std::size_t start)
{
    while (start < str.size() && str[start] == ' ') {
        ++start;
    }

    return start;
}

std::string trim(const std::string& str)
{
    auto start = str.begin();
    while (start != str.end() && isspace(*start)) {
        ++start;
    }

    if (start == str.end()) {
        return "";
    }

    auto rbegin = str.rbegin();
    while (rbegin != str.rend() && isspace(*rbegin)) {
        ++rbegin;
    }

    return { start, rbegin.base() };
}

bool startsWith(const std::string& str, const std::string& what)
{
    if (str.size() < what.size()) {
        return false;
    }

    for (std::size_t i = 0; i < what.size(); ++i) {
        if (str[i] != what[i]) {
            return false;
        }
    }

    return true;
}

bool startsWithCI(const std::string& str, const std::string& what)
{
    if (str.size() < what.size()) {
        return false;
    }

    for (std::size_t i = 0; i < what.size(); ++i) {
        if (tolower(str[i]) != tolower(what[i])) {
            return false;
        }
    }

    return true;
}

bool isOneOf(char c, const char* str)
{
    while (*str != '\0' && *str != c) {
        ++str;
    }

    return *str != '\0';
}

bool isOneOf(char c, const std::string& str)
{
    return isOneOf(c, str.c_str());
}

std::string::const_iterator readUntilWithForbidden(std::string::const_iterator begin,
                                                   const std::string::const_iterator& end,
                                                   char c,
                                                   const char* forbidden,
                                                   const std::string& msg)
{
    while (begin != end && *begin != c) {
        if (isOneOf(*begin, forbidden)) {
            throw ParseError(msg + ' ' + *begin);
        }
        ++begin;
    }

    return begin;
}

RLIB_END
