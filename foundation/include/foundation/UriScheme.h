#pragma once
#include <foundation/Defines.h>

RLIB_START

class RLIB_API UriScheme
{
public:
    UriScheme() = default;
    UriScheme(const std::string& scheme);
    UriScheme(const std::string::const_iterator& begin, const std::string::const_iterator& end);

    std::string toString() const;

    std::string::const_iterator parse(std::string::const_iterator begin, const std::string::const_iterator& end);

private:
    std::string _scheme;
};

RLIB_END
