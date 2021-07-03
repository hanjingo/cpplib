# 引入源文件
add_library(${PROJECT_NAME} 
    env.cpp 

    log/logger.cpp 
)

# 设置文件版本
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${CPPLIB_VERSION} SOVERSION ${CPPLIB_VERSION})

# 设置文件生成路径
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_PATH})

# 防止清理.so文件
set_target_properties(${PROJECT_NAME} PROPERTIES CLEAN_DIRECT_OUTPUT 1)

target_link_libraries(${PROJECT_NAME} 
    Boost::log
    Boost::log_setup
    Boost::chrono
    Boost::atomic
    Boost::filesystem
    Boost::regex
    Boost::thread
    Threads::Threads)