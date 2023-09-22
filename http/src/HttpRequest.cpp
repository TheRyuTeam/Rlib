#include <http/HttpRequest.h>

RLIB_START

HttpMethod HttpRequest::method() const noexcept
{
    return _method;
}

void HttpRequest::setMethod(HttpMethod method) noexcept
{
    _method = method;
}

Uri HttpRequest::path() const
{
    return _path;
}

void HttpRequest::setPath(const Uri& path)
{
    _path = path;
}

std::string HttpRequest::version() const
{
    return _version;
}

void HttpRequest::setVersion(const std::string& version)
{
    _version = version;
}

std::string HttpRequest::prop(const std::string& key) const
{
    if (key == "method") {
        return toString(_method);
    }
    if (key == "path") {
        return _path.toString();
    }
    if (key == "version") {
        return _version;
    }

    return Http::prop(key);
}

void HttpRequest::setProp(const std::string& key, const std::string& value)
{
    if (key == "method") {
        _method = fromString<HttpMethod>(value);
        return;
    }
    if (key == "path") {
        _path = value;
        return;
    }
    if (key == "version") {
        _version = value;
        return;
    }

    Http::setProp(key, value);
}

std::size_t HttpRequest::parseTop(const std::string& data)
{
    std::size_t i = 0;
    std::size_t e = data.find(' ');
    setProp("method", trim(data.substr(i, e - i)));
    i = skipWs(data, e + 1);
    e = data.find(' ', i);
    setProp("path", trim(data.substr(i, e - i)));
    i = skipWs(data, e + 1);
    e = data.find('\n');
    setProp("version", trim(data.substr(i, e - i)));
    i = data.find('\n', e);
    return i;
}

void HttpRequest::appendTop(std::ostream& ss) const
{
    ss << toString<HttpMethod>(_method) << ' ' << _path.toString() << ' ' << _version << "\r\n";
}

RLIB_END
