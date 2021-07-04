#include <string>
#include <iostream>
#include <chrono>
#include <thread>

#include "cpplib/util/error.hpp"
#include "cpplib/util/filepath.hpp"
#include "cpplib/util/defer.hpp"

namespace util = cpplib::util;

void testDefer() {
    defer(std::cout << "echo world" << std::endl);
    std::cout << "test: " << 
        "defer(std::cout << \"echo world\" << std::endl)" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    defer(std::cout << "echo hello" << std::endl);
    std::cout << "test: " << 
        "defer(std::cout << \"echo hello\" << std::endl)" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main(int argc, char* argv[]) {
    // test filepath
    std::cout << std::endl;
    std::cout << "start test filepath..." << std::endl;

    std::cout << "test: " << "util::Exist(\"/tmp\") = " << 
        util::IsExist("/tmp") << std::endl;

    std::cout << "test: " << "util::Pwd()->c_str() = " << 
        util::Pwd()->c_str() << std::endl;
    std::cout << std::endl;


    // test error
    std::cout << std::endl;
    std::cout << "start test error..." << std::endl;

    util::Error err1(1, "错误1");
    std::cout << "test: " << "util::Error err1(1, \"错误1\"); err1.Desc = " << 
        err1.Desc << std::endl;

    std::cout << std::endl;


    // test defer
    std::cout << std::endl;
    std::cout << "start test defer..." << std::endl;

    testDefer();

    std::cout << std::endl;


    // end
    std::cout << "test end..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(20));
}