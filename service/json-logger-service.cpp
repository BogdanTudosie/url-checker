#include "json-logger-service.h"

#include <fstream>

nlohmann::json JsonLoggerService::toJson(const CheckResult& result) {
    nlohmann::json json;
    json["url"] = result.getUrl();
    json["latency"] = result.getLatency();
    json["statusCode"] = result.getStatusCode();
    json["reachable"] = result.getStatusCode () >= 200 
            && result.getStatusCode() < 400;
    if (result.getErrorMessage().has_value()) {
        json["error"] = result.getErrorMessage().value();
    }

    return json;
}

void JsonLoggerService::log(const std::vector<CheckResult>& results) {
    nlohmann::json j = nlohmann::json::array();
    for (const auto& result: results) {
        nlohmann::json entry;
        entry = this->toJson(result);
        j.push_back(entry);
    }

    std::ofstream file(path);
    file << j.dump(4);
}

void JsonLoggerService::log(const std::unordered_map<std::string, CheckResult>& results) {
    nlohmann::json j = nlohmann::json::array();
    for (const auto& [key, result]: results) {
        j.push_back(toJson(result));
    }

    std::ofstream file(path);
    file << j.dump(4);
}

const std::string& JsonLoggerService::getPath() const { return path; }