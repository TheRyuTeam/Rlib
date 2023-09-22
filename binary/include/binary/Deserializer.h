#pragma once
#include "common.h"

namespace rlib
{

template <class T, class U = T>
class Deserializer;

template <class T>
class Deserializer<T, std::enable_if_t<std::is_integral<T>::value || std::is_floating_point<T>::value, T>>
{
public:
    static void deserialize(T& dest, binary_buffer& src)
    {
        const auto begin = src.begin();
        const auto end = begin + sizeof(dest);
        std::copy(begin, end, (byte_t*)&dest);
        src.erase(begin, end);
    }
};

template <class T>
class Deserializer<T, typename std::enable_if<std::is_enum<T>::value, T>::type>
{
public:
    static void deserialize(T& dest, binary_buffer& src)
    {
        using und_t = typename std::underlying_type<T>::type;
        und_t tmp;
        Deserializer<und_t>::deserialize(tmp, src);
        dest = static_cast<T>(tmp);
    }
};

template <>
class Deserializer<binary_buffer>
{
public:
    static void deserialize(binary_buffer& dest, binary_buffer& src)
    {
        dest.insert(dest.end(), src.begin(), src.end());
        src.clear();
    }
};

template <class T>
class Deserializer<T, typename std::enable_if<is_container<T>::value, T>::type>
{
public:
    static void deserialize(T& dest, binary_buffer& src)
    {
        using size_type = decltype(dest.size()); 
        using value_type = typename T::value_type;
        size_type size;
        Deserializer<size_type>::deserialize(size, src);
        for (size_type i = 0; i < size; ++i) {
            value_type value;
            Deserializer<value_type>::deserialize(value, src);
            dest.insert(dest.end(), value);
        }
    }
};

template <class T>
void deserialize(T& dest, binary_buffer& src)
{
    Deserializer<typename std::remove_reference<T>::type>::deserialize(dest, src);
}

}