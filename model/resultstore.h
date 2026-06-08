#ifndef _H_RESULTSTORE_H
#define _H_RESULTSTORE_H

#include <vector>
#include <unordered_map>
#include <string>
#include <optional>
#include <algorithm>
#include "check-result.h"

class ResultStore {
    public:
    ResultStore(const std::unordered_map<std::string, CheckResult>& results);
    std::optional<CheckResult> findByUrl(const std::string& url) const;
    std::vector<CheckResult> findByLatency(int minLatency) const;


    private:
    std::vector<CheckResult> byUrl;
    std::vector<CheckResult> byLatency;
};

#endif