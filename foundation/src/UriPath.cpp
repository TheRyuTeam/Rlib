#include <foundation/UriPath.h>
#include <foundation/StringUtils.h>
#include <foundation/Exception.h>

RLIB_START

UriPath::UriPath(const char* path)
    : UriPath(std::string(path))
{
}

UriPath::UriPath(const std::string& path)
    : UriPath(path.begin(), path.end())
{
}

UriPath::UriPath(const std::string::const_iterator& begin, const std::string::const_iterator& end)
    : _path()
{
    parse(begin, end);
}

bool UriPath::accepts(const UriPath& path) const
{
    return _path == path._path;
}

std::string UriPath::toString() const
{
    return '/' + join(_path, '/');
}

std::string::const_iterator UriPath::parse(std::string::const_iterator begin, const std::string::const_iterator& end)
{
    const char* pathForbiddenSymbols = "*?\"<>|&% '#[]+=„“";
    while (begin != end && *begin != '?' && *begin != '#') {
        auto it = begin;
        bool hasDot = false;
        while (it != end && *it != '/' && *it != '?' && *it != '#') {
            if (*it == '.') {
                hasDot = true;
            }
            if (isOneOf(*it, pathForbiddenSymbols)) {
                throw ParseError(std::string("Uri path can not contain ") + *it);
            }
            ++it;
        }

        if (it != end && *it == '/' && hasDot) {
            throw ParseError("Only last uri path element can contain '.'");
        }

        if (*it == '?' || *it == '#') {
            if (it - begin != 0) {
                _path.emplace_back(begin, it);
            }
            return it;
        }

        if (it - begin != 0) {
            _path.emplace_back(begin, it);
        } else {
            ++it;
        }

        begin = it;
    }

    return begin;
}

int UriPath::cmp(const UriPath& path) const
{
    auto cc = toString().compare(path.toString());
    return cc > 0 ? 1 : cc < 0 ? -1 : 0;
}

RLIB_END
