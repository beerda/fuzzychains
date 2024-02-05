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

FetchContent_Declare(googlebenchmark
    GIT_REPOSITORY https://github.com/google/benchmark.git
    GIT_TAG main)

FetchContent_MakeAvailable(
    googletest
    googlebenchmark)

add_subdirectory(src)
add_subdirectory(apps)
