set(HEADER_LIST
       "${fuzzychains_SOURCE_DIR}/include/common.h"
       "${fuzzychains_SOURCE_DIR}/include/BitsetNumChain.h")

set(CPP_LIST
       "${fuzzychains_SOURCE_DIR}/src/BitsetNumChain.cpp")

add_library(fuzzychains_lib STATIC "${HEADER_LIST}" "${CPP_LIST}")
target_sources(fuzzychains_lib PUBLIC "${HEADER_LIST}")
target_sources(fuzzychains_lib PUBLIC "${CPP_LIST}")
target_include_directories(fuzzychains_lib PUBLIC "${fuzzychains_SOURCE_DIR}/include/")

source_group(
    TREE "${PROJECT_SOURCE_DIR}/include"
    PREFIX "Header Files"
    FILES ${HEADER_LIST})

