cmake_minimum_required(VERSION 3.18)

project(fuzzychains
    VERSION 1.0
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG main)
    #GIT_TAG v1.10.x)

FetchContent_Declare(googlebenchmark
    GIT_REPOSITORY https://github.com/google/benchmark.git
    GIT_TAG main)

FetchContent_MakeAvailable(
    googletest
    googlebenchmark)

set(HEADER_LIST
    "${fuzzychains_SOURCE_DIR}/include/LukasIntFuzzyChain.h")

add_library(fuzzychains_lib INTERFACE)
target_sources(fuzzychains_lib INTERFACE "${HEADER_LIST}")
target_include_directories(fuzzychains_lib INTERFACE "${fuzzychains_SOURCE_DIR}/include/")

add_executable(fuzzychains main.cpp)
target_link_libraries(fuzzychains PRIVATE fuzzychains_lib benchmark::benchmark)
