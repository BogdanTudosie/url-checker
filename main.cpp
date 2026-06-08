
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <future>
#include <unordered_map>
#include "pool/thread-pool.h"
#include "http/http_client.h"
#include "model/check-result.h"
#include "service/url-checker-service.h"
#include "service/json-logger-service.h"

std::vector<std::string> readUrls(const std::string& path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file path");
    }

    std::vector<std::string> lines;
    std::string line;

    while(std::getline(file, line)) {
        if (!line.empty()) {
            lines.push_back(line);
        }
    }

    return lines;
}

int main() {
    ThreadPool pool(10);
    HttpClient httpClient;
    UrlCheckerService urlService(httpClient, pool);
    JsonLoggerService loggerService("output/log.json");

    std::cout << "Welcome to URL Checker!" << std::endl;
    std::vector<std::string> urls = readUrls("urls.txt");

    std::vector<std::future<CheckResult>> futures = urlService.queryUrls(urls);
    std::unordered_map<std::string, CheckResult> results;
    results.reserve(futures.size());

    for (auto& future : futures) {
        CheckResult result = future.get();
        std::string key = result.getUrl();
        results.emplace(std::move(key), std::move(result));
    }

    std::string target = urls[0];
    if (auto it = results.find(target); it != results.end()) {
        const CheckResult& r = it->second;
        std::cout << "URL: " << r.getUrl() << "\n";
        std::cout << "Status Code: " << r.getStatusCode() << "\n";
        std::cout << "Latency: " << r.getLatency() << "ms\n";
        if (r.getErrorMessage().has_value()) {
            std::cout << "Error: " << r.getErrorMessage().value() << "\n";
        }
    }

    loggerService.log(results);

    return 0;
}