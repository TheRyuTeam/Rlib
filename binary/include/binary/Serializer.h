#pragma once
#include "common.h"

namespace rlib
{

template <class T, class U = T>
class Serializer;

template <class T>
class Serializer<T, typename std::enable_if<std::is_integral<T>::value || std::is_floating_point<T>::value, T>::type>
{
public:
    static void serialize(binary_buffer& dest, const T& src)
    {
        const auto srcPtr = (const byte_t*)&src;
        dest.insert(dest.end(), srcPtr, srcPtr + sizeof(src));
    }
};

template <class T>
class Serializer<T, typename std::enable_if<std::is_enum<T>::value, T>::type>
{
public:
    static void serialize(binary_buffer& dest, const T& src)
    {
        using und_t = typename std::underlying_type<T>::type;
        Serializer<und_t>::serialize(dest, static_cast<und_t>(src));

    }
};

template <>
class Serializer<binary_buffer>
{
public:
    static void serialize(binary_buffer& dest, const binary_buffer& src)
    {
        dest.insert(dest.end(), src.begin(), src.end());
    }
};

template <class T>
class Serializer<T, typename std::enable_if<is_iterable<T>::value && !has_size<T>::value, T>::type>
{
public:
    static void serialize(binary_buffer& dest, const T& src)
    {
        std::size_t size = 0;
        binary_buffer tmp;
        for (const auto& x : src) {
            ++size;
            Serializer<decltype(x)>::serialize(tmp, src);
        }
        Serializer<decltype(size)>::serialize(dest, size);
        Serializer<decltype(tmp)>::serialize(dest, tmp);
    }
};

template <class T>
class Serializer<T, typename std::enable_if<is_iterable<T>::value && has_size<T>::value, T>::type>
{
public:
    static void serialize(binary_buffer& dest, const T& src)
    {
        Serializer<decltype(src.size())>::serialize(dest, src.size());
        for (const auto& x : src) {
            Serializer<typename std::remove_reference<decltype(x)>::type>::serialize(dest, x);
        }
    }
};

template <class T>
void serialize(binary_buffer& dest, const T& src)
{
    Serializer<T>::serialize(dest, src);
}

}