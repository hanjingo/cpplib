message("test util")

if(NOT DEFINED TEST_OUTPUT_PATH)
    set(TEST_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bins)
endif()

set(EXECUTABLE_OUTPUT_PATH ${TEST_OUTPUT_PATH})

# 生成文件
if(NOT DEFINED TEST_UTIL_NAME)
    set(TEST_UTIL_NAME util_test)
endif()

add_executable(${TEST_UTIL_NAME} 
    util_test.cpp)

target_link_libraries(${TEST_UTIL_NAME} 
    Boost::filesystem)