#pragma once

#include <string>
#include <iostream>
#include <memory>
#include <fstream>

#include <boost/log/common.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/support/date_time.hpp>

namespace cpplib {
namespace log {

namespace sinks    = boost::log::sinks;
namespace src      = boost::log::sources;
namespace expr     = boost::log::expressions;
namespace attrs    = boost::log::attributes;
namespace keywords = boost::log::keywords;
namespace file     = boost::log::sinks::file;
namespace trivial  = boost::log::trivial;

class Logger;

enum Lvl { DEBUG = 0, INFO = 1, WARN = 2, ERROR = 3, FATAL = 4 };
static std::ostream& operator<<(std::ostream& stream, Lvl lvl) {
  static const char* const LvlStr[] = {"DEBUG", "INFO", "WARN", "ERROR", "FATAL"};

  if (static_cast<std::size_t>(lvl) < sizeof(LvlStr) / sizeof(*LvlStr))
    stream << LvlStr[lvl];
  else
    stream << static_cast<int>(lvl);

  return stream;
};

// 以递归方式写入流
template<typename... Args, typename = typename std::enable_if<sizeof...(Args) == 0>::type>
static inline std::ostream& _output(std::ostream& stream, Args&&... args) { return stream; }

template<typename ArgType, typename... ArgTypes>
static inline std::ostream& _output(std::ostream& stream, ArgType&& arg, ArgTypes&&... args) {
  stream << arg;
  return _output(stream, std::forward<ArgTypes>(args)...);
}

// 格式化输入
template<typename... ArgTypes>
static inline std::string _format(ArgTypes&&... args) {
  std::ostringstream stream;
  cpplib::log::_output(stream, std::forward<ArgTypes>(args)...);
  return stream.str();
}

class Logger {
 public:
  typedef sinks::synchronous_sink<sinks::text_file_backend> file_sink;
  Logger();
  ~Logger();

  static std::shared_ptr<Logger> Instance() {
    if (_instance == 0)
      _instance = std::shared_ptr<Logger>(new Logger);
      return _instance;
  };

  /**
    * @brief 添加文件打印机
    * @param dir 文件目录
    * @param max_file_size_mb 文件最大大小(单位:mb)
    * @param max_backup 最多保存多少个文件
    * @param fmt 格式化处理器
    */
  void AddFileSink(const std::string& dir, int max_file_size_mb, int max_backup,
                   boost::log::formatter fmt);

  /**
    * @brief 添加打印机
    * @param fmt 格式化处理器
    */
  void AddConsoleSink(boost::log::formatter fmt);

  /**
    * @brief 设置日志等级
    * @param lvl 日志等级
    */
  void SetLvl(Lvl lvl);

  /**
    * @brief 默认格式处理器
    */
  static inline boost::log::formatter DefaultFormatter() {
    boost::log::formatter fmt = expr::stream
      << "[" << expr::format_date_time<boost::posix_time::ptime>(
        "TimeStamp", "%Y-%m-%d %H:%M:%S.%f")
      << "|" << expr::attr<Lvl>("Severity") << "]"
      << " " << expr::smessage;
    return fmt;
  };

  template<typename... ArgTypes>
  static inline void Debug(const std::string& fmt, ArgTypes&&... args) {
    BOOST_LOG_SEV(_slg, Lvl::DEBUG) << cpplib::log::_format(fmt, args...) << std::endl;
  }

  template<typename... ArgTypes>
  static inline void Info(const std::string& fmt, ArgTypes&&... args) {
    BOOST_LOG_SEV(_slg, Lvl::INFO) << cpplib::log::_format(fmt, args...) << std::endl;
  }

  template<typename... ArgTypes>
  static inline void Warn(const std::string& fmt, ArgTypes&&... args) {
    BOOST_LOG_SEV(_slg, Lvl::WARN) << cpplib::log::_format(fmt, args...) << std::endl;
  }

  template<typename... ArgTypes>
  static inline void Error(const std::string& fmt, ArgTypes&&... args) {
    BOOST_LOG_SEV(_slg, Lvl::ERROR) << cpplib::log::_format(fmt, args...) << std::endl;
  }

  template<typename... ArgTypes>
  static inline void Fatal(const std::string& fmt, ArgTypes&&... args) {
    BOOST_LOG_SEV(_slg, Lvl::ERROR) << cpplib::log::_format(fmt, args...) << std::endl;
  }

 private:
  static src::severity_logger<Lvl> _slg;        // boost.log实例
  static std::shared_ptr<Logger>   _instance;   // 单例
};

} // namespace cpplib
} // namespace log
