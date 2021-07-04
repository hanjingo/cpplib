#include <string>

#include "cpplib/env.hpp"
#include "cpplib/log/logger.hpp"

int main(int argc, char* argv[]) {
    std::cout << std::endl;
    std::cout << "start test log..." << std::endl;
    //cpplib::env::Init();
    auto log = cpplib::log::Logger::Instance();

    log->Info<std::string>("info:%s;", "cpplib");
    std::cout << std::endl;
}