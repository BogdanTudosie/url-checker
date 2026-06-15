#ifndef __URL-VALIDATOR_H__
#define __URL-VALIDATOR_H__

#include <string>

class UrlValidator {
    public:
        bool isValid(const std::string& url) const;
};

#endif // __URL-VALIDATOR_H__