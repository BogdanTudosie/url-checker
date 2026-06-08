cmake_minimum_required(VERSION 3.15)
project(url_checker)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)

add_executable(url_checker
               main.cpp
               http/http_client.cpp
               pool/thread-pool.cpp
               service/url-checker-service.cpp
               service/json-logger-service.cpp
               model/check-result.cpp
               model/resultstore.cpp
               )

target_include_directories(url_checker PRIVATE ${CMAKE_SOURCE_DIR})

target_link_libraries(url_checker 
    CURL::libcurl 
    nlohmann_json::nlohmann_json
)