#include <http/HttpServer.h>

RLIB_START

HttpServer::HttpServer(const SocketAddress& address, HttpRouter& router)
    : _address(address)
    , _events()
    , _router(router)
    , _working(false)
{
}

bool HttpServer::isWorking() const noexcept
{
    return _working;
}

void HttpServer::run()
{
    _events.clear();
    Socket server;
    server.bind(_address);
    server.listen(1024);
    _events.push_back(SocketPollEvent{ server, SocketPollEvent::SPE_IN });
    onServerStarted();
    _working = true;
    while (_working) {
        int rc = Socket::poll(_events, std::chrono::milliseconds(100));
        if (rc) {
            if (_events[0].revents & SocketPollEvent::SPE_IN) {
                 SocketAddress clientAddress;
                 Socket newClient = _events[0].socket.accept(clientAddress);
                 _events.push_back(SocketPollEvent{ newClient, SocketPollEvent::SPE_IN | SocketPollEvent::SPE_HUP | SocketPollEvent::SPE_HUP });
            }

            auto it = std::next(_events.begin());
            while (it != _events.end()) {
                if (it->revents & (SocketPollEvent::SPE_ERROR | SocketPollEvent::SPE_HUP)) {
                    it = _events.erase(it);
                    continue;
                }
                if (it->revents & SocketPollEvent::SPE_IN) {
                    char buff[4096]{};
                    int rc = it->socket.recv(buff, sizeof(buff), 0);
                    if (rc == 0) {
                        it = _events.erase(it);
                        continue;
                    }

                    auto data = onDataReceived(buff, rc);
                    data.setProp("source", it->socket.address().toString());
                    auto response = _router.handle(data);
                    auto sendData = response.data();
                    rc = it->socket.send((const char*)sendData.data(), sendData.size(), 0);
                    if (rc == 0) {
                        it = _events.erase(it);
                        continue;
                    }
                }
                ++it;
            }
        }
    }
    onServerStopped();
}

void HttpServer::stop()
{
    _working = false;
}

void HttpServer::onServerStarted()
{
}

void HttpServer::onServerStopped()
{
}

void HttpServer::onNewConnection(const SocketAddress&)
{
}

HttpRequest HttpServer::onDataReceived(const char* data, std::size_t)
{
    rlib::HttpRequest requestHeader;
    requestHeader.parse(data);
    return requestHeader;
}

RLIB_END
