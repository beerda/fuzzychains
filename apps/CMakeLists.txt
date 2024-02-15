add_compile_options(
    #-Wno-unused-parameter
    #-Wno-deprecated
    #-Wno-sign-compare
    #-Wno-ignored-qualifiers
    -march=native -mtune=native
    #-march=core2 -mtune=core2
    #-march=znver3 -mtune=znver3
    #-march=znver2 -mtune=znver2
    #-march=znver1 -mtune=znver1
    #-march=bdver1 -mtune=bdver1
)

add_executable(fuzzychains main.cpp)
#target_compile_features(fuzzychains PRIVATE cxx_std_17)
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
