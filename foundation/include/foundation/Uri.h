#pragma once
#include <foundation/UriPath.h>
#include <foundation/UriQuery.h>

RLIB_START

class Uri
{
public:
    Uri() = default;
    Uri(const std::string& uri);
    Uri(const std::string::const_iterator& begin, const std::string::const_iterator& end);

    UriPath path() const;
    UriQuery query() const;

    std::string toString() const;

    std::string::const_iterator parse(std::string::const_iterator begin, const std::string::const_iterator& end);

private:
    UriPath _path;
    UriQuery _query;
};


RLIB_END
