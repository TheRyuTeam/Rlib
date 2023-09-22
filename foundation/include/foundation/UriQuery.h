#pragma once
#include <foundation/Defines.h>
#include <string>
#include <map>

RLIB_START

class RLIB_API UriQuery
{
public:
    static constexpr const char* kForbiddenSymbols = "\"<>[]^`{|} ";

    UriQuery() = default;
    UriQuery(const std::string& query);
    UriQuery(const std::string::const_iterator& begin, const std::string::const_iterator& end);

    bool has(const std::string& key) const;

    std::string operator[](const std::string& key) const;
    std::string& operator[](const std::string& key);

    std::string toString() const;

    std::string::const_iterator parse(std::string::const_iterator it, const std::string::const_iterator& end);

private:
    std::map<std::string, std::string> _queries;
};

RLIB_END
