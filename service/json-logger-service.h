#ifndef _H_JSON_LOGGER_SERVICE_H
#define _H_JSON_LOGGER_SERVICE_H

#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "model/check-result.h"

class JsonLoggerService {
public:
    JsonLoggerService(const std::string &path) : path(path) {}
    void log(const std::vector<CheckResult>& results);
    nlohmann::json toJson(const CheckResult& result);
    const std::string& getPath() const;
private:
    std::string path;
};

#endif