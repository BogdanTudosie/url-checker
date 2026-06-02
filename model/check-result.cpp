#include "check-result.h"

#include <string>

const std::string& CheckResult::getUrl() const {
    return url;
}

int CheckResult::getLatency() const {
    return latency;
}

int CheckResult::getStatusCode() const {
    return statusCode;
}

const std::optional<std::string>& CheckResult::getErrorMessage() const {
    return errorMessage;
}