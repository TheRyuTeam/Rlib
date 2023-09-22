#include <net/SocketAddress.h>
#include "private/SocketAddressV4Impl.h"
#include "private/SocketAddressV6Impl.h"

RLIB_START

SocketAddress::SocketAddress()
    : _impl(new SocketAddressV4Impl)
{
}

SocketAddress::SocketAddress(uint32_t addr, uint16_t port)
    : _impl(new SocketAddressV4Impl(addr, port))
{
}

SocketAddress::SocketAddress(const byte_t addr[16], uint16_t port)
    : _impl(new SocketAddressV6Impl(addr, port))
{
}

SocketAddress::SocketAddress(const char* addr, uint16_t port)
    : _impl(nullptr)
{
    try {
        _impl.reset(new SocketAddressV4Impl(addr, port));
    } catch (...) {
        try {
            _impl.reset(new SocketAddressV6Impl(addr, port));
        } catch (...) {
            throw SocketAddressParseError("Can not parse inet address \"" + std::string(addr) + "\"");
        }
    }
}

int SocketAddress::af() const
{
    return _impl->af();
}

bool SocketAddress::isV4() const
{
    return _impl->isV4();
}

uint16_t SocketAddress::port() const
{
    return _impl->port();
}

std::string SocketAddress::toString() const
{
    return _impl->toString();
}

const char* SocketAddress::paddr() const
{
    return _impl->paddr();
}

int SocketAddress::plen() const
{
    return _impl->plen();
}

SocketAddress::SocketAddress(const char* addr, DummySize size)
    : _impl(nullptr)
{
    auto pAddr = (const sockaddr*)addr;
    if (pAddr->sa_family == AF_INET6) {
        if (size.size < sizeof(sockaddr_in6)) {
            throw SocketAddressParseError("Invalid addr v6 length");
        }
        auto v6pAddr = (const sockaddr_in6*)addr;
        _impl.reset(new SocketAddressV6Impl(v6pAddr->sin6_addr.__in6_u.__u6_addr8, ntohs(v6pAddr->sin6_port)));
    } else {
        if (size.size < sizeof(sockaddr_in)) {
            throw SocketAddressParseError("Invalid addr v4 length");
        }
        auto v4pAddr = (const sockaddr_in*)addr;
        _impl.reset(new SocketAddressV4Impl(v4pAddr->sin_addr.s_addr, ntohs(v4pAddr->sin_port)));
    }
}

RLIB_END