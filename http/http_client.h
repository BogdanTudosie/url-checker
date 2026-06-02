#ifndef _H_HTTP_CLIENT_H_
#define _H_HTTP_CLIENT_H_

#include <string>

struct HttpResponse {
    int statusCode;
    int latency;
};

class HttpClient {
public:
    HttpResponse fetch(const std::string& url);
};

#endif // _H_HTTP_CLIENT_H_