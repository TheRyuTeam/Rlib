#include <http/HttpResponse.h>
#include <foundation/StringUtils.h>

RLIB_START

HttpResponse::HttpResponse(long code)
    : _code(static_cast<HttpStatusCode>(code))
{
}

HttpResponse::HttpResponse(HttpStatusCode code)
    : _code(code)
{
}

std::string HttpResponse::version() const
{
    return _version;
}

void HttpResponse::setVersion(const std::string& version)
{
    _version = version;
}

HttpStatusCode HttpResponse::code() const noexcept
{
    return _code;
}

void HttpResponse::setCode(long code) noexcept
{
    setCode(static_cast<HttpStatusCode>(code));
}

void HttpResponse::setCode(HttpStatusCode code) noexcept
{
    _code = code;
}

std::string HttpResponse::message() const
{
    return _message ? *_message : make_message(_code);
}

void HttpResponse::setMessage(const std::string& message)
{
    if (!_message) {
        _message = new std::string();
    }
    *_message = message;
}

std::string HttpResponse::prop(const std::string& key) const
{
    if (key == "version") {
        return _version;
    }
    if (key == "code") {
        return std::to_string(_code);
    }

    if (key == "message") {
        return message();
    }

    return Http::prop(key);
}

void HttpResponse::setProp(const std::string& key, const std::string& value)
{
    if (key == "version") {
        _version = value;
        return;
    }
    if (key == "code") {
        _code = fromString<HttpStatusCode>(value);
        return;
    }
    if (key == "message") {
        setMessage(value);
        return;
    }

    Http::setProp(key, value);
}


std::size_t HttpResponse::parseTop(const std::string& data)
{
    std::size_t prio = static_cast<std::size_t>(-1);
    std::size_t i = 0;
    std::size_t e = data.find(' ');
    auto piece = trim(data.substr(i, e - i));
    if (!isdigit(piece[0])) {
        setProp("version", piece);
        i = skipWs(data, e + 1);
        e = data.find(' ', i);
        piece = trim(data.substr(i, e - i));
    }

    setProp("code", piece);
    i = skipWs(data, e + 1);
    e = data.find(' ', i);
    setProp("message", trim(data.substr(i, e - i)));
    i = skipWs(data, e + 1);
    return i;
}

void HttpResponse::appendTop(std::ostream& ss) const
{
    ss << prop("version") << ' ' << prop("code") << ' ' << prop("message") << "\r\n";
}

RLIB_END
