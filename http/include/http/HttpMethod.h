#pragma once
#include <foundation/StringUtils.h>

RLIB_START

enum class HttpMethod : uint16_t
{
    None    = 0x00,
    Get     = 0x01,
    Head    = 0x02,
    Post    = 0x04,
    Delete  = 0x08,
    Connect = 0x10,
    Options = 0x20,
    Trace   = 0x40,
    Patch   = 0x80,
};

namespace {

static constexpr std::pair<HttpMethod, const char*> _names[] = {
    { HttpMethod::Get, "GET" },
    { HttpMethod::Head, "HEAD" },
    { HttpMethod::Post, "POST" },
    { HttpMethod::Delete, "DELETE" },
    { HttpMethod::Connect, "CONNECT" },
    { HttpMethod::Options, "OPTIONS" },
    { HttpMethod::Trace, "TRACE" },
    { HttpMethod::Patch, "PATCH" },
};

}

template <>
inline HttpMethod fromString<HttpMethod>(const std::string& str)
{
    const auto begin = str.begin();
    const auto end = str.end();
    for (const auto& name : _names) {
        auto it = begin;
        auto nameIt = name.second;
        while (it != end && *nameIt != '\0' && *it == *nameIt) {
            ++it;
            ++nameIt;
        }

        if (*nameIt == '\0') {
            return name.first;
        }
    }

    return HttpMethod::None;
}

template <>
inline std::string toString<HttpMethod>(const HttpMethod& value)
{
    std::string str;
    for (const auto& name : _names) {
        if (name.first == value) {
            auto nameIt = name.second;
            while (*nameIt != '\0') {
                str += *nameIt++;
            }
        }
    }

    return str;
}

RLIB_END
