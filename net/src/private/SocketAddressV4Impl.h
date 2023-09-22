#pragma once
#include <net/SocketAddress.h>
#include <foundation/Exception.h>

#include <arpa/inet.h>

RLIB_START

class SocketAddressV4Impl
    : public ISocketAddress
{
public:
    SocketAddressV4Impl();
    SocketAddressV4Impl(uint32_t addr, uint16_t port);
    SocketAddressV4Impl(const char* addr, uint16_t port);
    
    int af() const override;
    bool isV4() const override;
    uint16_t port() const override;
    std::string toString() const override;
    const char* paddr() const override;
    int plen() const override;

private:
    sockaddr_in _addr;
};

inline SocketAddressV4Impl::SocketAddressV4Impl()
    : _addr()
{
}

inline SocketAddressV4Impl::SocketAddressV4Impl(uint32_t addr, uint16_t port)
    : SocketAddressV4Impl()
{
    _addr.sin_family = AF_INET;
    _addr.sin_addr = { addr };
    _addr.sin_port = htons(port);
}

inline SocketAddressV4Impl::SocketAddressV4Impl(const char* addr, uint16_t port)
    : SocketAddressV4Impl()
{
    _addr.sin_family = AF_INET;
    if (!inet_aton(addr, &_addr.sin_addr)) {
        throw SocketAddressParseError("Invalid ipv4 address \"" + std::string(addr) + "\"");
    }
    _addr.sin_port = htons(port);
}

int SocketAddressV4Impl::af() const
{
    return _addr.sin_family;
}

inline bool SocketAddressV4Impl::isV4() const
{
    return true;
}

inline uint16_t SocketAddressV4Impl::port() const
{
    return ntohs(_addr.sin_port);
}

inline std::string SocketAddressV4Impl::toString() const
{
    return std::string(inet_ntoa(_addr.sin_addr)) + ':' + std::to_string(port());
}

inline const char* SocketAddressV4Impl::paddr() const
{
    return (const char*)&_addr;
}

inline int SocketAddressV4Impl::plen() const
{
    return sizeof(_addr);
}

RLIB_END