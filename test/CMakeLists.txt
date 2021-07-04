if(NOT DEFINED TEST_OUTPUT_PATH)
    set(TEST_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bins)
endif()

if(${TEST_UTIL} STREQUAL "ON")
    add_subdirectory(util)
endif()

if(${TEST_LOG} STREQUAL "ON")
    add_subdirectory(log)
endif()