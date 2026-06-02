#ifndef _H_CHECK_RESULT_H_
#define _H_CHECK_RESULT_H_

#include <optional>
#include <string>

class CheckResult {
public:
    CheckResult(std::string url, int statusCode, int latency, std::optional<std::string> errorMessage)
        : url(std::move(url)), statusCode(statusCode), latency(latency), 
          errorMessage(std::move(errorMessage)) {}

    // getters so the logger can read the data
    const std::string& getUrl() const;
    int getStatusCode() const;
    int getLatency() const;
    const std::optional<std::string>& getErrorMessage() const;

private:
    std::string url;
    int statusCode;
    int latency;
    std::optional<std::string> errorMessage;
};

#endif