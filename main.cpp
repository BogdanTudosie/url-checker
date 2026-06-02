
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <future>
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
    std::vector<CheckResult> results;
    for (auto& f: futures) {
        results.push_back(f.get());
    }

    loggerService.log(results);

    return 0;
}