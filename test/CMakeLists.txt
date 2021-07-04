if(NOT DEFINED TEST_OUTPUT_PATH)
    set(TEST_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bins)
endif()

add_subdirectory(util) # 测试util
add_subdirectory(log) # 测试log