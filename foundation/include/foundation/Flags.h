#pragma once
#include <foundation/Defines.h>
#include <type_traits>

RLIB_START

template <class T>
class RLIB_API Flags
{
public:
    static_assert(std::is_enum<T>::value, "Expected enum as Flags template parameter");

    using enum_type = T;
    using value_type = typename std::underlying_type<enum_type>::type;

    Flags(T flags = static_cast<enum_type>(0))
        : _flags(flags)
    {
    }

    Flags(value_type flags)
        : _flags(static_cast<enum_type>(flags))
    {
    }

    value_type flags() const noexcept
    {
        return static_cast<value_type>(_flags);
    }

    operator bool() const noexcept
    {
        return flags() != static_cast<value_type>(0);
    }

    Flags<T>& set(T flag)
    {
        _flags = static_cast<enum_type>(flags() | static_cast<value_type>(flag));
        return *this;
    }

    Flags<T>& unset(T flag)
    {
        _flags = static_cast<enum_type>(flags() & ~static_cast<value_type>(flag));
        return *this;
    }

    Flags<T>& set(T flag, bool on)
    {
        if (on) {
            return set(flag);
        }

        return unset(flag);
    }

    bool testAny(value_type flag) const
    {
        return flags() & flag;
    }

    bool testAny(T flag) const
    {
        return testAny(static_cast<value_type>(flag));
    }

    bool testAny(Flags<T> flags) const
    {
        return testAny(flags._flags);
    }

    bool test(value_type flag) const
    {
        if (flag == 0 && flags() == 0) {
            return true;
        }

        return testAny(flag);
    }

    bool test(T flag) const
    {
        return test(static_cast<value_type>(flag));
    }

    bool test(Flags<T> flags) const
    {
        return test(flags._flags);
    }

    bool operator==(const Flags<T>& flag) const
    {
        return flags() == flag;
    }

    bool operator!=(const Flags<T>& flag) const
    {
        return flags() != flag.flags();
    }

    Flags<T> operator|(const Flags<T>& flag) const
    {
        return Flags<T>(flags() | flag.flags());
    }

    Flags<T>& operator|=(const Flags<T>& flag)
    {
        return *this = *this | flag;
    }

    Flags<T> operator&(const Flags<T>& flag) const
    {
        return Flags<T>(flags() & flag.flags());
    }

    Flags<T>& operator&=(const Flags<T>& flag)
    {
        return *this = *this & flag;
    }

    Flags<T> operator^(const Flags<T>& flag) const
    {
        return Flags<T>(flags() ^ flag.flags());
    }

    Flags<T>& operator^=(const Flags<T>& flag)
    {
        return *this = *this ^ flag;
    }

    Flags<T> operator~() const
    {
        return Flags<T>(~flags());
    }

private:
    T _flags;
};

RLIB_END
