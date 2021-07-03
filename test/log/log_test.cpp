#include <string>

#include "cpplib/log/logger.hpp"

int main(int argc, char* argv[]) {
    std::cout << "start test log" << std::endl;
    auto log = cpplib::log::Logger::Instance();

    //std::cout << "test: " << log->Info<char*>() << std::endl;
}