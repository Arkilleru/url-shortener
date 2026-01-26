#pragma once

#include <userver/server/handlers/http_handler_base.hpp>
#include <unordered_map>
#include <shared_mutex>

namespace url_shortener::handlers {

class Shortener final : public userver::server::handlers::HttpHandlerBase {
public:
    static constexpr std::string_view kName = "handler-url-shortener";

    using HttpHandlerBase::HttpHandlerBase;

    std::string HandleRequestThrow(
        const userver::server::http::HttpRequest& request,
        userver::server::request::RequestContext&) const override;

private:
    mutable std::unordered_map<std::string, std::string> storage_;
    mutable std::shared_mutex mutex_;
};

} // namespace url_shortener::handlers