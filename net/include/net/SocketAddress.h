#pragma once
#include <foundation/Defines.h>
#include <memory>
#include <string>

RLIB_START

class RLIB_API ISocketAddress
{
public:
    virtual ~ISocketAddress() = default;
    virtual int af() const = 0;
    virtual bool isV4() const = 0;
    virtual uint16_t port() const = 0;
    virtual std::string toString() const = 0;
    virtual const char* paddr() const = 0;
    virtual int plen() const = 0;
};

class RLIB_API SocketAddress
    : public ISocketAddress
{
public:
    SocketAddress();
    SocketAddress(uint32_t addr, uint16_t port);
    SocketAddress(const byte_t addr[16], uint16_t port);
    SocketAddress(const char* addr, uint16_t port);
    
    int af() const override;
    bool isV4() const override;
    uint16_t port() const override;
    std::string toString() const override;
    const char* paddr() const override;
    int plen() const override;

private:
    struct DummySize
    {
        socklen_t size;
    };

    SocketAddress(const char* addr, DummySize size);

private:
    std::shared_ptr<ISocketAddress> _impl;
    friend class SocketImpl;
    friend class Socket;
};

RLIB_END

namespace std
{

inline std::string to_string(const RLIB_NS::SocketAddress& address)
{
    return address.toString();
}

}
