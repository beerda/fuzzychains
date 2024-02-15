add_compile_options(
    -Wno-unused-parameter
    -Wno-deprecated 
    -Wno-sign-compare 
    -Wno-ignored-qualifiers
)

add_executable(fuzzychains "${fuzzychains_SOURCE_DIR}/apps/main.cpp")
target_compile_features(fuzzychains PRIVATE cxx_std_17)
target_link_libraries(fuzzychains PRIVATE fuzzychains_lib benchmark::benchmark)

add_executable(unittest
    unittest_BitwiseFuzzyChain_goedel.cpp
    unittest_BitwiseFuzzyChain_goguen.cpp
    unittest_BitwiseFuzzyChain_lukasiewicz.cpp
    unittest_VectorFuzzyChain.cpp
)
target_link_libraries(unittest PRIVATE fuzzychains_lib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(unittest)
