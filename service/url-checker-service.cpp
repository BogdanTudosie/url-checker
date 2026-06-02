#include <iostream>
#include "url-checker-service.h"

CheckResult UrlCheckerService::queryUrl(const std::string& url) {
    try {
        HttpResponse response = httpClient.fetch(url);
        std::cout << "Verifying url: " << url << "\n";
        return CheckResult(url, response.statusCode, response.latency, std::nullopt);
    } catch (const std::exception& e) {
        return CheckResult(url, 0, 0, std::string(e.what()));
    }
}

std::vector<std::future<CheckResult>> UrlCheckerService::queryUrls(const std::vector<std::string>& urls) {
    std::vector<std::future<CheckResult>> futures;
    for (const auto& url: urls) {
        futures.push_back(threadPool.submit([this, url]() -> CheckResult {
            return queryUrl(url);
        }));
    }

    return futures;
}