#include <foundation/Uri.h>

RLIB_START

Uri::Uri(const std::string& uri)
    : Uri(uri.begin(), uri.end())
{
}

Uri::Uri(const std::string::const_iterator& begin, const std::string::const_iterator& end)
    : _path()
    , _query()
{
    parse(begin, end);
}

UriPath Uri::path() const
{
    return _path;
}

UriQuery Uri::query() const
{
    return _query;
}

std::string Uri::toString() const
{
    return _path.toString() + _query.toString();
}

std::string::const_iterator Uri::parse(std::string::const_iterator begin, const std::string::const_iterator& end)
{
    begin = _path.parse(begin, end);
    begin = _query.parse(begin, end);
    return begin;
}

RLIB_END
