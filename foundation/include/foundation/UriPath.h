#pragma once
#include <foundation/Defines.h>
#include <string>
#include <vector>
#include <map>

RLIB_START

class RLIB_API UriPath
{
public:
    UriPath() = default;
    UriPath(const char* path);
    UriPath(const std::string& path);
    UriPath(const std::string::const_iterator& begin, const std::string::const_iterator& end);

    bool accepts(const UriPath& path) const;

    std::string toString() const;

    std::string::const_iterator parse(std::string::const_iterator begin, const std::string::const_iterator& end);

    int cmp(const UriPath& path) const;

private:
    std::vector<std::string> _path;
};

PP_GEN_CMP_OP(UriPath)

RLIB_END
