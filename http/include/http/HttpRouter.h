#pragma once
#include <http/HttpRequest.h>
#include <http/HttpResponse.h>
#include <foundation/Flags.h>
#include <functional>

RLIB_START

class RLIB_API HttpRouter
{
public:
    using processor_t = std::function<HttpResponse(const HttpRequest&)>;
    class ReqProcessor
    {
    public:
        ReqProcessor()
        {
        }

        ReqProcessor(const processor_t& processor, const Flags<HttpMethod>& allowedMethods)
            : _processor(processor)
            , _allowedMethods(allowedMethods)
        {
        }

        bool accepts(HttpMethod method)
        {
            return _allowedMethods & method;
        }

        auto process(const HttpRequest& request)
        {
            return _processor(request);
        }

    private:
        processor_t _processor;
        Flags<HttpMethod> _allowedMethods;
        friend class HttpRouter;
    };

    HttpResponse handle(HttpRequest& request);

    void setErrorProcessor(const processor_t& processor);

    void onGet(const UriPath& path, const processor_t& processor);
    void onHead(const UriPath& path, const processor_t& processor);
    void onPost(const UriPath& path, const processor_t& processor);
    void onDelete(const UriPath& path, const processor_t& processor);
    void onConnect(const UriPath& path, const processor_t& processor);
    void onOptions(const UriPath& path, const processor_t& processor);
    void onTrace(const UriPath& path, const processor_t& processor);
    void onPatch(const UriPath& path, const processor_t& processor);

private:
    void _setProcessor(const UriPath& path, const ReqProcessor& processor);

private:
    std::map<UriPath, ReqProcessor> _handlers;
    processor_t _onRoutingError;
};


/// @section HttpRouter inlines
inline void HttpRouter::onGet(const UriPath& path, const processor_t& processor)
{
    _setProcessor(path, { processor, HttpMethod::Get });
}

inline void HttpRouter::onHead(const UriPath& path, const processor_t& processor)
{
    _setProcessor(path, { processor, HttpMethod::Head });
}

inline void HttpRouter::onPost(const UriPath& path, const processor_t& processor)
{
    _setProcessor(path, { processor, HttpMethod::Post });
}

inline void HttpRouter::onDelete(const UriPath& path, const processor_t& processor)
{
    _setProcessor(path, { processor, HttpMethod::Delete });
}

inline void HttpRouter::onConnect(const UriPath& path, const processor_t& processor)
{
    _setProcessor(path, { processor, HttpMethod::Connect });
}

inline void HttpRouter::onOptions(const UriPath& path, const processor_t& processor)
{
    _setProcessor(path, { processor, HttpMethod::Options });
}

inline void HttpRouter::onTrace(const UriPath& path, const processor_t& processor)
{
    _setProcessor(path, { processor, HttpMethod::Trace });
}

inline void HttpRouter::onPatch(const UriPath& path, const processor_t& processor)
{
    _setProcessor(path, { processor, HttpMethod::Patch });
}

RLIB_END
