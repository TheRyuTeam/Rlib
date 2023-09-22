#pragma once
#include <foundation/StringUtils.h>

RLIB_START

enum HttpStatusCode : long
{
    Continue = 100,
    SwitchingProtocols = 101,
    Processing = 102,
    EarlyHints = 103,
    OK = 200,
    Created = 201,
    Accepted = 202,
    NonAuthoritativeInformation = 203,
    NoContent = 204,
    ResetContent = 205,
    PartialContent = 206,
    MultiStatus = 207,
    AlreadyReported = 208,
    IMUsed = 226,
    MultipleChoices = 300,
    MovedPermanently = 301,
    Found = 302,
    SeeOther = 303,
    NotModified = 304,
    UseProxy = 305,
    TemporaryRedirect = 307,
    PermanentRedirect = 308,
    BadRequest = 400,
    Unauthorized = 401,
    PaymentRequired = 402,
    Forbidden = 403,
    NotFound = 404,
    MethodNotAllowed = 405,
    NotAcceptable = 406,
    ProxyAuthenticationRequired = 407,
    RequestTimeout = 408,
    Conflict = 409,
    Gone = 410,
    LengthRequired = 411,
    PreconditionFailed = 412,
    PayloadTooLarge = 413,
    URITooLong = 414,
    UnsupportedMediaType = 415,
    RangeNotSatisfiable = 416,
    ExpectationFailed = 417,
    ImTeapot = 418,
    AuthenticationTimeout = 419,
    MisdirectedRequest = 421,
    UnprocessableEntity = 422,
    Locked = 423,
    FailedDependency = 424,
    TooEarly = 425,
    UpgradeRequired = 426,
    PreconditionRequired = 428,
    TooManyRequests = 429,
    RequestHeaderFieldsTooLarge = 431,
    RetryWith = 449,
    UnavailableForLegalReasons = 451,
    ClientClosedRequest = 499,
    InternalServerError = 500,
    NotImplemented = 501,
    BadGateway = 502,
    ServiceUnavailable = 503,
    GatewayTimeout = 504,
    HTTPVersionNotSupported = 505,
    VariantAlsoNegotiates = 506,
    InsufficientStorage = 507,
    LoopDetected = 508,
    BandwidthLimitExceeded = 509,
    NotExtended = 510,
    NetworkAuthenticationRequired = 511,
    UnknownError = 520,
    WebServerIsDown = 521,
    ConnectionTimedOut = 522,
    OriginIsUnreachable = 523,
    ATimeoutOccurred = 524,
    SSLHandshakeFailed = 525,
    InvalidSSLCertificate = 526,
};

template <>
inline HttpStatusCode fromString<HttpStatusCode>(const std::string& str)
{
    return static_cast<HttpStatusCode>(std::stol(str));
}

template <>
inline std::string toString<HttpStatusCode>(const HttpStatusCode& code)
{
    return std::to_string(static_cast<long>(code));
}

inline std::string make_message(const HttpStatusCode& code)
{
    switch (code) {
        case HttpStatusCode::Continue:
            return "Continue";
        case HttpStatusCode::SwitchingProtocols:
            return "Switching Protocols";
        case HttpStatusCode::Processing:
            return "Processing";
        case HttpStatusCode::EarlyHints:
            return "Early Hints";
        case HttpStatusCode::OK:
            return "OK";
        case HttpStatusCode::Created:
            return "Created";
        case HttpStatusCode::Accepted:
            return "Accepted";
        case HttpStatusCode::NonAuthoritativeInformation:
            return "Non-Authoritative Information";
        case HttpStatusCode::NoContent:
            return "No Content";
        case HttpStatusCode::ResetContent:
            return "Reset Content";
        case HttpStatusCode::PartialContent:
            return "Partial Content";
        case HttpStatusCode::MultiStatus:
            return "Multi-Status";
        case HttpStatusCode::AlreadyReported:
            return "Already Reported";
        case HttpStatusCode::IMUsed:
            return "IM Used";
        case HttpStatusCode::MultipleChoices:
            return "Multiple Choices";
        case HttpStatusCode::MovedPermanently:
            return "Moved Permanently";
        case HttpStatusCode::Found:
            return "Found";
        case HttpStatusCode::SeeOther:
            return "See Other";
        case HttpStatusCode::NotModified:
            return "Not Modified";
        case HttpStatusCode::UseProxy:
            return "Use Proxy";
        case HttpStatusCode::TemporaryRedirect:
            return "Temporary Redirect";
        case HttpStatusCode::PermanentRedirect:
            return "Permanent Redirect";
        case HttpStatusCode::BadRequest:
            return "Bad Request";
        case HttpStatusCode::Unauthorized:
            return "Unauthorized";
        case HttpStatusCode::PaymentRequired:
            return "Payment Required";
        case HttpStatusCode::Forbidden:
            return "Forbidden";
        case HttpStatusCode::NotFound:
            return "Not Found";
        case HttpStatusCode::MethodNotAllowed:
            return "Method Not Allowed";
        case HttpStatusCode::NotAcceptable:
            return "Not Acceptable";
        case HttpStatusCode::ProxyAuthenticationRequired:
            return "Proxy Authentication Required";
        case HttpStatusCode::RequestTimeout:
            return "Request Timeout";
        case HttpStatusCode::Conflict:
            return "Conflict";
        case HttpStatusCode::Gone:
            return "Gone";
        case HttpStatusCode::LengthRequired:
            return "Length Required";
        case HttpStatusCode::PreconditionFailed:
            return "Precondition Failed";
        case HttpStatusCode::PayloadTooLarge:
            return "Payload Too Large";
        case HttpStatusCode::URITooLong:
            return "URI Too Long";
        case HttpStatusCode::UnsupportedMediaType:
            return "Unsupported Media Type";
        case HttpStatusCode::RangeNotSatisfiable:
            return "Range Not Satisfiable";
        case HttpStatusCode::ExpectationFailed:
            return "Expectation Failed";
        case HttpStatusCode::ImTeapot:
            return "Im a teapot";
        case HttpStatusCode::AuthenticationTimeout:
            return "Authentication Timeout";
        case HttpStatusCode::MisdirectedRequest:
            return "Misdirected Request";
        case HttpStatusCode::UnprocessableEntity:
            return "Unprocessable Entity";
        case HttpStatusCode::Locked:
            return "Locked";
        case HttpStatusCode::FailedDependency:
            return "Failed Dependency";
        case HttpStatusCode::TooEarly:
            return "Too Early";
        case HttpStatusCode::UpgradeRequired:
            return "Upgrade Required";
        case HttpStatusCode::PreconditionRequired:
            return "Precondition Required";
        case HttpStatusCode::TooManyRequests:
            return "Too Many Requests";
        case HttpStatusCode::RequestHeaderFieldsTooLarge:
            return "Request Header Fields Too Large";
        case HttpStatusCode::RetryWith:
            return "Retry With";
        case HttpStatusCode::UnavailableForLegalReasons:
            return "Unavailable For Legal Reasons";
        case HttpStatusCode::ClientClosedRequest:
            return "Client Closed Request";
        case HttpStatusCode::InternalServerError:
            return "Internal Server Error";
        case HttpStatusCode::NotImplemented:
            return "Not Implemented";
        case HttpStatusCode::BadGateway:
            return "Bad Gateway";
        case HttpStatusCode::ServiceUnavailable:
            return "Service Unavailable";
        case HttpStatusCode::GatewayTimeout:
            return "Gateway Timeout";
        case HttpStatusCode::HTTPVersionNotSupported:
            return "HTTP Version Not Supported";
        case HttpStatusCode::VariantAlsoNegotiates:
            return "Variant Also Negotiates";
        case HttpStatusCode::InsufficientStorage:
            return "Insufficient Storage";
        case HttpStatusCode::LoopDetected:
            return "Loop Detected";
        case HttpStatusCode::BandwidthLimitExceeded:
            return "Bandwidth Limit Exceeded";
        case HttpStatusCode::NotExtended:
            return "Not Extended";
        case HttpStatusCode::NetworkAuthenticationRequired:
            return "Network Authentication Required";
        case HttpStatusCode::UnknownError:
            return "Unknown Error";
        case HttpStatusCode::WebServerIsDown:
            return "Web Server Is Down";
        case HttpStatusCode::ConnectionTimedOut:
            return "Connection Timed Out";
        case HttpStatusCode::OriginIsUnreachable:
            return "Origin Is Unreachable";
        case HttpStatusCode::ATimeoutOccurred:
            return "A Timeout Occurred";
        case HttpStatusCode::SSLHandshakeFailed:
            return "SSL Handshake Failed";
        case HttpStatusCode::InvalidSSLCertificate:
            return "Invalid SSL Certificate";
    }

    return "UNKNOWN";
}

RLIB_END
