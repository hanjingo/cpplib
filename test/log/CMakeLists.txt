message("test util")

if(NOT DEFINED TEST_OUTPUT_PATH)
    set(TEST_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bins)
endif()

set(EXECUTABLE_OUTPUT_PATH ${TEST_OUTPUT_PATH})

# log测试文件
if(NOT DEFINED TEST_LOG_NAME)
    set(TEST_LOG_NAME tlog)
endif()
add_executable(${TEST_LOG_NAME} log_test.cpp)

add_dependencies(${TEST_LOG_NAME} cpplib)
target_link_libraries(${TEST_LOG_NAME} cpplib)