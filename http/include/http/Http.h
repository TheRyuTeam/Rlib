#pragma once
#include <foundation/Defines.h>
#include <ostream>
#include <vector>
#include <map>

RLIB_START

class Http
{
public:
    virtual ~Http() = default;
    Http();
    void parse(const std::string& data);

    std::vector<byte_t> data() const;

    virtual std::string prop(const std::string& key) const;
    virtual void setProp(const std::string& key, const std::string& value);

protected:
    virtual std::size_t parseTop(const std::string& str) = 0;
    virtual void appendTop(std::ostream&) const = 0;

private:
    std::map<std::string, std::string> _props;
    std::string _body;
};

RLIB_END
