#include "cpplib/env.hpp"

namespace cpplib {
namespace env {

void Init() {
    // 配置log
    cpplib::log::Logger::Instance()->SetLvl(cpplib::log::Lvl::DEBUG);
}

}
}