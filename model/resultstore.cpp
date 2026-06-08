#include "resultstore.h"

ResultStore::ResultStore(const std::unordered_map<std::string, CheckResult>& results) {
    for(const auto& [key, result]: results) {
        byUrl.push_back(result);
        byLatency.push_back(result);
    }

    std::sort(byUrl.begin(), byUrl.end(), [](const CheckResult& a, const CheckResult& b) {
        return a.getUrl() < b.getUrl();
    });

    std::sort(byLatency.begin(), byLatency.end(), [](const CheckResult& a, const CheckResult& b) {
        return a.getLatency() < b.getLatency();
    });
}

std::optional<CheckResult> ResultStore::findByUrl(const std::string& url) const {
    auto it = std::lower_bound(byUrl.begin(), byUrl.end(), url, [](const CheckResult& result, const std::string& url) {
        return result.getUrl() < url;
    });

    if (it != byUrl.end() && it->getUrl() == url) {
        return *it;
    }

    return std::nullopt;
}

std::vector<CheckResult> ResultStore::findByLatency(int minLatency) const {
    auto it = std::lower_bound(byLatency.begin(), byLatency.end(), minLatency, [](const CheckResult& result, int latency) {
        return result.getLatency() < latency;
    });
    return std::vector<CheckResult>(it, byLatency.end());
}