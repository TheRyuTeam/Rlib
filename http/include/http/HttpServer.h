#pragma once
#include <http/HttpRouter.h>
#include <net/Socket.h>

RLIB_START

class HttpServer
{
public:
    HttpServer(const SocketAddress& address, HttpRouter& router);
    virtual ~HttpServer() = default;

    bool isWorking() const noexcept;
    void run();
    void stop();

protected:
    virtual void onServerStarted();
    virtual void onServerStopped();
    virtual void onNewConnection(const SocketAddress&);
    virtual HttpRequest onDataReceived(const char* data, std::size_t);

private:
    SocketAddress _address;
    std::vector<SocketPollEvent> _events;
    HttpRouter& _router;
    bool _working;
};

RLIB_END
