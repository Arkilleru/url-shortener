#pragma once
#include <unordered_set>
#include <string_view>
#include <string>

namespace url_shortener::utils {

inline bool IsBanned(const std::string& url) {
    static const std::unordered_set<std::string_view> kBannedDomains = {
        "bit.ly", "tinyurl.com", "t.co", "malware.ru"
    };

    for (const auto& domain : kBannedDomains) {
        if (url.find(domain) != std::string::npos) return true;
    }
    return false;
}

} // namespace url_shortener::utils