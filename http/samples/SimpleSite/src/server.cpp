#include <http/HttpServer.h>
#include <iostream>
#include <sstream>
#include <fstream>

std::size_t cmpLen(const std::string& a, const std::string& b)
{
    std::size_t i = 0;
    while (i < a.size() && i < b.size() && a[i] == b[i]) {
        ++i;
    }

    return i;
}

std::string readWhole(const std::string& file)
{
    std::string str;
    std::ifstream f(file);
    while (true) {
        constexpr int maxLen = 4096;
        char buff[maxLen]{};
        int len = 0;
        while (len < maxLen) {
            char c = f.get();
            if (c == EOF) {
                str.insert(str.end(), buff, buff + len);
                return str;
            }
            buff[len++] = c;
        }
        str.insert(str.end(), buff, buff + len);
    }

    return str;
}

const std::string kIndexFilename = "index.html";
const std::string kLoginFilename = "login.html";
const std::string kFaviconFilename = "mail_icon.ico";



class Message
{
public:
    Message(const std::string& source, const std::string& message)
        : _source(source)
        , _message(message)
        , _timestamp(std::chrono::system_clock::now())
    {
    }

    std::string source() const { return _source; }
    std::string message() const { return _message; }
    std::chrono::system_clock::time_point timestamp() const { return _timestamp; }

private:
    std::string _source;
    std::string _message;
    std::chrono::system_clock::time_point _timestamp;
};

class User
{
public:
    User(const std::string& login, const std::string& password)
        : _login(login)
        , _password(password)
    {
    }

    std::string _login;
    std::string _password;
};

std::vector<Message> _msgs;
std::map<std::string, std::string> psewdo;
std::vector<User> _users;

rlib::HttpResponse onRoutingError(const rlib::HttpRequest&)
{
    return rlib::HttpStatusCode::NotFound;
}

rlib::HttpResponse sendHtmlFile(const std::string& filename, std::map<std::string, std::string> props = {})
{
    auto data = readWhole(filename);
    rlib::HttpResponse response(rlib::HttpStatusCode::OK);
    response.setProp("Content-Type", "text/html; charset=utf-8\r\n");
    for (const auto& p : props) {
        response.setProp(p.first, p.second);
    }
    response.setProp("body", data);
    return response;
}

rlib::HttpResponse indexRequest(const rlib::HttpRequest& header)
{
    auto userIt = psewdo.find(header.prop("source"));
    if (userIt == psewdo.end()) {
        return sendHtmlFile(kLoginFilename);
    } else {
        return sendHtmlFile(kIndexFilename);
    }
}

rlib::HttpResponse faviconRequest(const rlib::HttpRequest&)
{
    auto data = readWhole(kFaviconFilename);
    rlib::HttpResponse response(rlib::HttpStatusCode::OK);
    response.setProp("Content-Type", "image/x-icon");
    response.setProp("body", data);
    return response;
}

rlib::HttpResponse newMessage(const rlib::HttpRequest& header)
{
    auto fIt = psewdo.find(header.prop("source"));
    if (fIt == psewdo.end()) {
        return rlib::HttpStatusCode::Forbidden;
    }

    _msgs.emplace_back(fIt->second, header.prop("body"));
    return rlib::HttpStatusCode::OK;
}

template <class T>
std::string toString(T value, int size, char fill = ' ')
{
    std::string str = std::to_string(value);
    if (size > 0 && str.size() < size) {
        auto s = size - str.size();
        str.insert(str.begin(), s, fill);
    }
    if (size < 0 && str.size() < -size) {
        str.insert(str.end(), -size - str.size(), fill);
    }
    return str;
}

template <class T>
std::string toString0(T value, int size)
{
    return toString(value, size, '0');
}

rlib::HttpResponse allMessages(const rlib::HttpRequest& header)
{
    auto fIt = psewdo.find(header.prop("source"));
    if (fIt == psewdo.end()) {
        return rlib::HttpStatusCode::Forbidden;
    }

    std::stringstream ss;
    for (std::size_t i = 0; i < _msgs.size(); ++i) {
        auto& msg = _msgs[i];
        auto src = psewdo[msg.source()];
        if (src.empty()) {
            src = msg.source();
        }
        std::time_t now_c = std::chrono::system_clock::to_time_t(msg.timestamp());
        std::tm now_tm = *std::localtime(&now_c);
        ss << src << "<&!&>" << toString0(now_tm.tm_mday, 2) << '.'
           << toString0(now_tm.tm_mon, 2) << '.' << toString0(now_tm.tm_year, 4) << ' ' << toString0(now_tm.tm_hour, 2) << ':'
           << toString0(now_tm.tm_min, 2) << ':' << toString0(now_tm.tm_sec, 2) << "<&!&>"
           << msg.message() << "<&!&>" << (int)(fIt->second == src) << "<!&!>";
    }

    rlib::HttpResponse response(rlib::HttpStatusCode::OK);
    response.setProp("Content-Type", "text/plain; charset=utf-8\r\n");
    response.setProp("body", ss.str());
    return response;
}

rlib::HttpResponse onLogin(const rlib::HttpRequest& header)
{
    rlib::Uri uri = rlib::Uri(header.prop("path"));
    auto login = uri.query()["login"];
    auto password = uri.query()["password"];
    for (const auto& user : _users) {
        if (user._login == login && user._password == password) {
            psewdo[header.prop("source")] = login;
            return rlib::HttpStatusCode::OK;
        }
    }

    return rlib::HttpStatusCode::Forbidden;
}

rlib::HttpResponse onRegister(const rlib::HttpRequest& header)
{
    rlib::Uri uri = rlib::Uri(header.prop("path"));
    auto login = uri.query()["login"];
    auto password = uri.query()["password"];
    for (const auto& user : _users) {
        if (user._login == login) {
            return rlib::HttpStatusCode::NotAcceptable;
        }
    }

    _users.push_back(User(login, password));
    psewdo[header.prop("source")] = login;
    return rlib::HttpStatusCode::OK;
}

rlib::HttpResponse onLogout(const rlib::HttpRequest& header)
{
    psewdo.erase(header.prop("source"));
    return rlib::HttpStatusCode::OK;
}

rlib::HttpResponse onGetOwnLogin(const rlib::HttpRequest& header)
{
    auto fIt = psewdo.find(header.prop("source"));
    if (fIt == psewdo.end()) {
        return rlib::HttpStatusCode::Forbidden;
    }

    rlib::HttpResponse response(rlib::HttpStatusCode::OK);
    response.setProp("Content-Type", "text/plain; charset=utf-8\r\n");
    response.setProp("body", fIt->second);
    return response;
}


int main()
{
    _users.emplace_back("admin", "");

    using rlib::SocketAddress;
    using rlib::Socket;
    using rlib::SocketPollEvent;

    rlib::HttpRouter router;
    router.setErrorProcessor(onRoutingError);
    router.onGet("/", indexRequest);
    router.onPost("/message", newMessage);
    router.onPost("/allMessages", allMessages);
    router.onPost("/login", onLogin);
    router.onPost("/register", onRegister);
    router.onPost("/logout", onLogout);
    router.onPost("/myLogin", onGetOwnLogin);

    rlib::HttpServer httpServer(SocketAddress("127.0.0.1", 12345), router);
    httpServer.run();

    return 0;
}
