#pragma once

namespace cpplib {
namespace util {

// 模拟go的defer
template<typename T>
class deferClass {
public:
  explicit deferClass(T&& t) : _fun {std::move(t)} {}
  ~deferClass() { _fun(); }

private:
  T _fun;
};

} // namespace cpplib
} // namespace util

template<typename T>
cpplib::util::deferClass<T> make_defer(T&& t) {
  return cpplib::util::deferClass<T> {std::forward<T>(t)};
}

#define DEFER_1(x, y) x##y
#define DEFER_2(x, y) DEFER_1(x, y)
#define DEFER_3(x)    DEFER_2(x, __COUNTER__)
#define defer(code)   auto DEFER_3(_defer_) = make_defer([&](){code;})