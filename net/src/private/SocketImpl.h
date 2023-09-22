#pragma once
#include <net/Socket.h>
#include <net/Exception.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <iostream>

RLIB_START

using socket_t = int;
constexpr int kInvalidSocket = -1;

class SocketImpl
{
public:
    SocketImpl(socket_t socket = kInvalidSocket)
        : _fd(socket)
    {
    }

    ~SocketImpl()
    {
        close();
    }

    SocketImpl(int domain, int type, int protocol)
        : _fd(::socket(domain, type, protocol))
    {
        if (_fd == kInvalidSocket) {
            auto err = getError();
            throw SocketError(err);
        }
    }

    void close()
    {
        ::close(_fd);
        _fd = kInvalidSocket;
    }

    bool valid() const noexcept
    {
        return _fd != kInvalidSocket;
    }

    void init(int domain, int type, int protocol)
    {
        _fd = ::socket(domain, type, protocol);
        if (_fd == kInvalidSocket) {
            auto err = getError();
            throw SocketError(err);
        }
    }

    void bind(const SocketAddress& address, std::errc& error)
    {
        error = ::bind(_fd, (const sockaddr*)address.paddr(), address.plen()) != 0 ? getError() : std::errc();
    }

    void listen(int backlog, std::errc& error)
    {
        error =  ::listen(_fd, backlog) != 0 ? getError() : std::errc();
    }

    std::shared_ptr<SocketImpl> accept(SocketAddress& address, std::errc& error)
    {
        sockaddr addr{};
        socklen_t len = sizeof(addr);
        socket_t accepted = ::accept(_fd, &addr, &len);
        if (accepted == kInvalidSocket) {
            error = getError();
            return nullptr;
        }

        error = std::errc();
        address = SocketAddress((const char*)&addr, SocketAddress::DummySize{ len });
        return std::shared_ptr<SocketImpl>(new SocketImpl(accepted));
    }

    void connect(const SocketAddress& address, std::errc& error)
    {
        error = ::connect(_fd, (const sockaddr*)address.paddr(), address.plen()) != 0 ? getError() : std::errc();
    }

    int recv(char* buff, int maxLen, std::errc& error, int flags)
    {
        int rc = ::recv(_fd, buff, maxLen, flags);
        if (rc == -1)
        {
            error = getError();
            return 0;    
        }
        error = std::errc();
        return rc;
    }

    int send(const char* buff, int len, std::errc& error, int flags)
    {
        int rc = ::send(_fd, buff, len, flags);
        if (rc == -1)
        {
            error = getError();
            return 0;    
        }
        error = std::errc();
        return rc;
    }

    static std::errc getError()
    {
        return static_cast<std::errc>(errno);
    }

    int cmp(const SocketImpl& other) const
    {
        if (_fd != other._fd) {
            return _fd > other._fd ? 1 : -1;
        }

        return 0;
    }

    socket_t fd() const noexcept
    {
        return _fd;
    }

private:
    socket_t _fd;
};

RLIB_END
