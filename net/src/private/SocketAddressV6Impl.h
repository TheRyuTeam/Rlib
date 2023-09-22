#pragma once
#include <net/SocketAddress.h>
#include <foundation/Exception.h>
#include <arpa/inet.h>

RLIB_START

class SocketAddressV6Impl
    : public ISocketAddress
{
public:
    SocketAddressV6Impl()
        : _addr()
    {
    }

    SocketAddressV6Impl(const byte_t addr[16], uint16_t port)
        : _addr()
    {
        _addr.sin6_family = AF_INET6;
        for (int i = 0; i < 16; ++i) {
            _addr.sin6_addr.s6_addr[i] = addr[i];
        }
        _addr.sin6_port = htons(port);
    }

    SocketAddressV6Impl(const char* addr, uint16_t port)
        : _addr()
    {
        if (inet_pton(AF_INET6, addr, &_addr) != 1) {
            throw SocketAddressParseError("Invalid ipv6 address \"" + std::string(addr) + "\"");
        }
    }

    int af() const override
    {
        return _addr.sin6_family;
    }
    
    bool isV4() const override
    {
        return false;
    }

    uint16_t port() const override
    {
        return ntohs(_addr.sin6_port);
    }

    std::string toString() const override
    {
        static char buff[INET6_ADDRSTRLEN];
        inet_ntop(AF_INET6, &_addr, buff, sizeof(buff));
        return '[' + std::string(buff) + "]:" + std::to_string(port());
    }

    const char* paddr() const override
    {
        return (const char*)&_addr;
    }

    int plen() const override
    {
        return sizeof(_addr);
    }

private:
    sockaddr_in6 _addr;
};

RLIB_END