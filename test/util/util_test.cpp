#include <string>
#include <iostream>

#include "cpplib/util/error.hpp"
#include "cpplib/util/filepath.hpp"

namespace util = cpplib::util;

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
    std::cout << "start test error..." << std::endl;

    util::Error err1(1, "错误1");
    std::cout << "test: " << "util::Error err1(1, \"错误1\"); err1.Desc = " << 
        err1.Desc << std::endl;

    std::cout << std::endl;
}