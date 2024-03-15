set(HEADER_LIST
    "${fuzzychains_SOURCE_DIR}/include/common.h"
    "${fuzzychains_SOURCE_DIR}/include/AlignedAllocator.h"
    "${fuzzychains_SOURCE_DIR}/include/BitwiseFuzzyChain.h"
    "${fuzzychains_SOURCE_DIR}/include/VectorFuzzyChain.h")

add_library(fuzzychains_lib INTERFACE)
target_sources(fuzzychains_lib INTERFACE "${HEADER_LIST}")
target_include_directories(fuzzychains_lib INTERFACE "${fuzzychains_SOURCE_DIR}/include/")

#source_group(
    #TREE "${PROJECT_SOURCE_DIR}/include"
    #PREFIX "Header Files"
    #FILES ${HEADER_LIST})

