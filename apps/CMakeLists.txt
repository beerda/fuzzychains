add_compile_options(
    -Wno-unused-parameter
    -Wno-deprecated 
    -Wno-sign-compare 
    -Wno-ignored-qualifiers
)

add_executable(fuzzychains "${fuzzychains_SOURCE_DIR}/apps/main.cpp")
target_compile_features(fuzzychains PRIVATE cxx_std_17)

target_link_libraries(fuzzychains PRIVATE fuzzychains_lib benchmark::benchmark)

