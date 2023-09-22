#pragma once
#include <http/Http.h>
#include <http/HttpCode.h>

RLIB_START

class RLIB_API HttpResponse
    : public Http
{
public:
    HttpResponse() = default;
    HttpResponse(long code);
    HttpResponse(HttpStatusCode code);

    std::string version() const;
    void setVersion(const std::string& version);

    HttpStatusCode code() const noexcept;
    void setCode(long code) noexcept;
    void setCode(HttpStatusCode code) noexcept;

    std::string message() const;
    void setMessage(const std::string& message);

    std::string prop(const std::string& key) const override;
    void setProp(const std::string& key, const std::string& value) override;

protected:
    std::size_t parseTop(const std::string& data) override;
    void appendTop(std::ostream& ss) const override;

private:
    std::string _version    = "HTTP/1.1";
    HttpStatusCode _code    = HttpStatusCode::OK;
    std::string* _message   = nullptr;
};

RLIB_END
