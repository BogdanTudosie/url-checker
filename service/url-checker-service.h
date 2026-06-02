#ifndef _H_URL_CHECKER_SERVICE_H
#define _H_URL_CHECKER_SERVICE_H

#include <string>
#include <vector>
#include <future>
#include "http/http_client.h"
#include "pool/thread-pool.h"
#include "model/check-result.h"

class UrlCheckerService {
public:
    explicit UrlCheckerService(HttpClient& httpClient, ThreadPool& threadPool) 
        : httpClient(httpClient), threadPool(threadPool) {}
    CheckResult queryUrl(const std::string& url);
    std::vector<std::future<CheckResult>> queryUrls(const std::vector<std::string>& urls);

private:
    HttpClient& httpClient;
    ThreadPool& threadPool;
};

#endif