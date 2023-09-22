#include <foundation/UriScheme.h>
#include <foundation/Exception.h>

RLIB_START

UriScheme::UriScheme(const std::string& scheme)
    : UriScheme(scheme.begin(), scheme.end())
{
}

UriScheme::UriScheme(const std::string::const_iterator& begin, const std::string::const_iterator& end)
    : _scheme()
{
    parse(begin, end);
}

std::string UriScheme::toString() const
{
    return _scheme;
}

std::string::const_iterator UriScheme::parse(std::string::const_iterator begin, const std::string::const_iterator& end)
{
    if (begin == end) {
        return begin;
    }

    auto it = begin;
    if (isalpha(*it++)) {
        throw ParseError("Uri scheme must start from alpha");
    }

    while (it != end && *it != ':') {
        if (!isalnum(*it) && *it != '+' && *it != '-' && *it != '.') {
            throw ParseError("Uri scheme must consist of (alpha | digit | + | + | .)");
        }
        ++it;
    }

    _scheme = std::string(begin, it);
    if (it != end) {
        ++it;
    }

    return it;
}

RLIB_END
