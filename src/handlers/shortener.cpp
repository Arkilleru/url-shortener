#include "shortener.hpp"
#include "../utils/blacklist.hpp"

#include <userver/crypto/hash.hpp>
#include <userver/server/http/http_status.hpp>

namespace url_shortener::handlers {

std::string Shortener::HandleRequestThrow(
    const userver::server::http::HttpRequest& request,
    userver::server::request::RequestContext&) const {

  if (request.GetMethod() == userver::server::http::HttpMethod::kPost) {
    const auto& long_url = request.GetArg("url");

    if (long_url.empty()) {
        request.SetResponseStatus(userver::server::http::HttpStatus::kBadRequest);
        return "Error: argument 'url' is required\n";
    }

    if (url_shortener::utils::IsBanned(long_url)) {
      request.SetResponseStatus(userver::server::http::HttpStatus::kForbidden);
      return "Error: this domain is blacklisted!\n";
    }

    std::string id = userver::crypto::hash::Sha256(long_url).substr(0, 6);

    {
      std::unique_lock lock(mutex_);
      storage_[id] = long_url;
    }

    return "Shortened: http://localhost:8080/v1/shorten?id=" + id + "\n";
  }

  const auto& id = request.GetArg("id");
  if (!id.empty()) {
    std::shared_lock lock(mutex_); 
    auto it = storage_.find(id);
    
    if (it != storage_.end()) {
      auto& response = request.GetHttpResponse();
      response.SetStatus(userver::server::http::HttpStatus::kFound);
      response.SetHeader(std::string{"Location"}, it->second);
      return "";
    }
    
    request.SetResponseStatus(userver::server::http::HttpStatus::kNotFound);
    return "Error: ID not found\n";
  }

  return "Usage: POST with ?url=... to shorten, GET with ?id=... to redirect\n";
}

} // namespace url_shortener::handlers