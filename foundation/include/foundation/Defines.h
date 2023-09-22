#pragma once
#include <cstdint>
#include <type_traits>
#include <iterator>

#define RLIB_NS rlib
#define RLIB_START namespace RLIB_NS {
#define RLIB_END }
#define RLIB_API
#define PP_ALL(x) std::begin(x), std::end(x)

RLIB_START

template <class... Dummy>
using void_t = void;

template <class T, class = void>
struct is_iterable
    : std::false_type
{
};

template <class T>
struct is_iterable<T, void_t<decltype(std::begin(std::declval<T&>())), decltype(std::end(std::declval<T&>()))>>
    : std::true_type
{
};

template <class T, class = void>
struct has_end_insert
    : std::false_type
{
};

template <class T>
struct has_end_insert<T, void_t<decltype(std::declval<T&>().push_back())>>
    : std::true_type
{
};

template <class T, class = void>
struct has_size : std::false_type
{
};

template <class T>
struct has_size<T, void_t<decltype(std::declval<T&>().size())>>
    : std::true_type
{
};

template <class T, class = void>
struct is_container
    : std::false_type
{
};

template <class T>
struct is_container<T, void_t<typename T::size_type, typename T::value_type,
    decltype(std::declval<T&>().insert(std::begin(std::declval<T&>()), std::declval<typename T::value_type>())),
    decltype(std::declval<T&>().size())>>
    : std::true_type
{
};

template <class T, class = void>
struct has_toString
    : std::false_type
{
};

template <class T>
struct has_toString<T, void_t<decltype(std::declval<T>().toString())>>
    : std::false_type
{
};

using byte_t = uint8_t;
using socklen_t = unsigned int;

template <class T, class U>
T exchange(T& a, const U& b)
{
    T tmp = a;
    a = b;
    return tmp;
}

RLIB_END

#define PP_GEN_CMP_OP(Class)\
inline bool operator==(const Class& a, const Class& b)\
{\
    return a.cmp(b) == 0;\
}\
inline bool operator!=(const Class& a, const Class& b)\
{\
    return !(a == b);\
}\
inline bool operator<(const Class& a, const Class& b)\
{\
    return a.cmp(b) < 0;\
}\
inline bool operator>(const Class& a, const Class& b)\
{\
    return a.cmp(b) > 0;\
}\
inline bool operator<=(const Class& a, const Class& b)\
{\
    return a.cmp(b) <= 0;\
}\
inline bool operator>=(const Class& a, const Class& b)\
{\
    return a.cmp(b) >= 0;\
}

template <class T>
class EqualWith
{
public:
    EqualWith(T value)
        : _value(value)
    {
    }

    bool operator()(const T& other) const
    {
        return other == _value;
    }

private:
    T _value;
};
