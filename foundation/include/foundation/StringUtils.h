#pragma once
#include <foundation/Defines.h>
#include <string>
#include <functional>

RLIB_START

std::size_t skipWs(const std::string& str, std::size_t start);

std::string trim(const std::string& str);

bool startsWith(const std::string& str, const std::string& what);

bool startsWithCI(const std::string& str, const std::string& what);

bool isOneOf(char c, const char* str);
bool isOneOf(char c, const std::string& str);

std::string::const_iterator readUntilWithForbidden(std::string::const_iterator begin,
                                                   const std::string::const_iterator& end,
                                                   char c,
                                                   const char* forbidden,
                                                   const std::string& msg = "Forbidden symbol");

template <class T>
T fromString(const std::string& str);

template <class T, class U = T>
class ToStringConverter;

template <class T>
class ToStringConverter<T, typename std::enable_if<std::is_same<decltype(std::to_string(std::declval<T>())), std::string>::value, T>::type>
{
public:
    static std::string toString(T value)
    {
        return std::to_string(value);
    }
};

template <class T>
class ToStringConverter<T, typename std::enable_if<std::is_convertible<T, std::string>::value, T>::type>
{
    static std::string toString(T value)
    {
        return static_cast<std::string>(value);
    }
};

template <class T>
class ToStringConverter<T, typename std::enable_if<has_toString<T>::value, T>::type>
{
    static std::string toString(const T& value)
    {
        return value.toString();
    }
};

template <class T>
std::string toString(const T& value)
{
    return ToStringConverter<T>::toString(value);
}

template <class Cont>
std::string join(const Cont& cont, char delim, const std::function<std::string(const typename Cont::value_type&)>& joinRule)
{
    auto it = std::begin(cont);
    auto next = std::next(it);
    const auto end = std::end(cont);

    std::string ret;
    if (it != end) {
        while (next != end) {
            ret += joinRule(*it) + delim;
            ++it;
            ++next;
        }

        ret += joinRule(*it);
    }

    return ret;
}

template <class Cont>
std::string join(const Cont& cont, char delim)
{
    return join(cont, delim, [](const typename Cont::value_type& value) {
        return value;
    });
}

RLIB_END
