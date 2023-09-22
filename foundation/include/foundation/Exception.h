#pragma once
#include <foundation/Defines.h>
#include <stdexcept>
#include <string>
#include <system_error>

RLIB_START

class Exception
    : public std::exception
{
public:
    Exception(const char* msg)
        : _msg(msg)
    {
    }

    Exception(const std::string& msg)
        : _msg(msg)
    {
    }

    Exception(std::string&& msg)
        : _msg(std::move(msg))
    {
    }

    const std::string& msg() const
    {
        return _msg;
    }

    const char* what() const noexcept override
    {
        return _msg.c_str();
    }

private:
    std::string _msg;
};

class ParseError
    : public Exception
{
public:
    using Exception::Exception;
};

class SocketAddressParseError
    : public Exception
{
public:
    using Exception::Exception;
};

RLIB_END
