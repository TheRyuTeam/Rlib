#pragma once
#include <net/SocketAddress.h>
#include <system_error>
#include <chrono>
#include <vector>

RLIB_START

struct RLIB_API SocketPollEvent;

class RLIB_API SocketImpl;

class RLIB_API Socket
{
public:
    using Ptr = std::shared_ptr<Socket>;

    Socket();
    void bind(const SocketAddress& address);
    void listen(int backlog);
    Socket accept(SocketAddress& address);

    void connect(const SocketAddress& address);
    int recv(char* buff, int maxLen, int flags);
    int send(const char* buff, int len, int flags);

    static int poll(std::vector<SocketPollEvent>& events, std::chrono::milliseconds timeout = std::chrono::milliseconds(0));
    int cmp(const Socket& other) const;

    bool isValid() const noexcept;
    SocketAddress address() const;

private:
    Socket(const std::shared_ptr<SocketImpl>& impl);
    void init(int domain, int type, int protocol);

private:
    std::shared_ptr<SocketImpl> _impl;
};

struct RLIB_API SocketPollEvent
{
    enum Event: short
    {
        SPE_NONE = 0,
        SPE_IN = 1,
        SPE_PRI = 2,
        SPE_OUT = 4,
        SPE_ERROR = 8,
        SPE_HUP = 16,
        SPE_NVAL = 32,
        SPE_RDNORM = 64,
        SPE_RDBAND = 128,
        SPE_WRNORM = 256,
        SPE_WRBAND = 512,
        SPE_MSG = 1024
    };

    Socket socket;
    Event events;
    Event revents;  
};

inline SocketPollEvent::Event operator|(SocketPollEvent::Event a, SocketPollEvent::Event b)
{
    return static_cast<SocketPollEvent::Event>((short)a | (short)b);
}

void make_socket_error(std::errc code);

PP_GEN_CMP_OP(Socket)

RLIB_END
