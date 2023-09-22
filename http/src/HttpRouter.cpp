#include <http/HttpRouter.h>

RLIB_START

HttpResponse HttpRouter::handle(HttpRequest& request)
{
    try {
        const Uri uri = request.path();
        const UriPath path = uri.path();
        const HttpMethod method = request.method();
        for (auto& handler : _handlers) {
            if (handler.second.accepts(method) && handler.first.accepts(path)) {
                return handler.second.process(request);
            }
        }
    } catch (...) {
    }

    return _onRoutingError(request);
}

void HttpRouter::setErrorProcessor(const processor_t& processor)
{
    _onRoutingError = processor;
}

void HttpRouter::_setProcessor(const UriPath& path, const ReqProcessor& processor)
{
    auto it = _handlers.find(path);
    if (it == _handlers.end()) {
        _handlers[path] = processor;
    } else {
        it->second._allowedMethods |= processor._allowedMethods;
    }
}

RLIB_END
