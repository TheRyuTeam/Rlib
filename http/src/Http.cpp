#include <http/Http.h>
#include <foundation/StringUtils.h>
#include <sstream>

RLIB_START

Http::Http()
    : _props()
    , _body()
{
    _props["Content-Length"] = "0";
}

void Http::parse(const std::string& data)
{
    std::size_t i = parseTop(data);
    while (i < data.size()) {
        i = data.find_first_not_of('\n', i);
        std::size_t e = data.find(':', i);
        if (e == std::string::npos) {
            break;
        }
        const std::string propName = data.substr(i, e - i);
        ++e;
        i = skipWs(data, e);
        e = data.find('\n', i);
        _props[propName] = trim(data.substr(i, e - i));
        i = e;
        if (i < data.size() && data[i] == '\n' && i + 1 < data.size() && data[i + 1] == '\n') {
            break;
        }
        ++i;
    }
    _body = trim(data.substr(i, data.size() - i));
}

std::string Http::prop(const std::string& key) const
{
    if (key == "body") {
        return _body;
    }

    auto it = _props.find(key);
    return it != _props.end() ? it->second : "";
}

void Http::setProp(const std::string& key, const std::string& value)
{
    if (key == "Content-Length") {
        throw 1;
    }

    if (key == "body") {
        _body = value;
        _props["Content-Length"] = std::to_string(_body.length());
        return;
    }

    _props[key] = value;
}

std::vector<byte_t> Http::data() const
{
    std::stringstream ss;
    appendTop(ss);
    for (const auto& prop : _props) {
        ss << prop.first << ": " << prop.second << "\r\n";
    }

    ss << _body;
    const std::string str = ss.str();
    return { str.begin(), str.end() };
}

RLIB_END
