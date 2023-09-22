#pragma once
#include <http/Http.h>
#include <http/HttpMethod.h>
#include <foundation/Uri.h>

RLIB_START

class RLIB_API HttpRequest
    : public Http
{
public:
    HttpMethod method() const noexcept;
    void setMethod(HttpMethod method) noexcept;

    Uri path() const;
    void setPath(const Uri& path);

    std::string version() const;
    void setVersion(const std::string& version);

    std::string prop(const std::string& key) const override;
    void setProp(const std::string& key, const std::string& value) override;

protected:
    std::size_t parseTop(const std::string& data) override;
    void appendTop(std::ostream& ss) const override;

private:
    HttpMethod _method;
    Uri _path;
    std::string _version;
};

RLIB_END
