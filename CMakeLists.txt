cmake_minimum_required(VERSION 3.19.2)
project(cpplib)

set(CPPLIB_VERSION 0.0.1)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bins)
set(TEST_LOG OFF) # 编译log测试程序
set(TEST_UTIL ON) # 编译util测试程序

# 打开c++11
add_definitions(-std=c++11)

# 导入boost组件
add_definitions(-DBOOST_LOG_DYN_LINK)
find_package(Threads REQUIRED) 
find_package(Boost 1.75.0 REQUIRED COMPONENTS 
    log 
    log_setup 
    chrono 
    atomic 
    filesystem 
    regex 
    thread) 

# 导入头文件
include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

# 添加子目录
add_subdirectory(src) # 源文件
add_subdirectory(test) # 测试
#add_subdirectory(sample) # 示例