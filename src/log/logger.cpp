#include "cpplib/log/logger.hpp"

namespace cpplib {
namespace log {

std::shared_ptr<Logger>                   Logger::_instance;
boost::log::sources::severity_logger<Lvl> Logger::_slg;

// 添加常用属性(LineID, TimeStamp, ProcessID, ThreadID)
Logger::Logger() { boost::log::add_common_attributes(); }
Logger::~Logger() {}

void Logger::AddFileSink(const std::string& dir, int max_file_size_mb, 
                         int max_backup, boost::log::formatter fmt) {
  boost::shared_ptr<file_sink> fileSink(new file_sink(
      keywords::target_file_name    = "%Y%m%d_%H%M%S_%N.log",                 // 文件命名规则
      keywords::time_based_rotation = file::rotation_at_time_point(0, 0, 0),  // 文件寿命
      keywords::rotation_size       = max_file_size_mb * 1024 * 1024,         // 文件最大尺寸
      keywords::open_mode           = std::ios::out | std::ios::app));        // 文件打开模式

  fileSink->locked_backend()->set_file_collector(file::make_collector(
      keywords::target         = dir,                                           // 文件夹名字
      keywords::max_size       = max_backup * max_file_size_mb * 1024 * 1024,   // 文件夹log所占最大空间
      keywords::min_free_space = max_backup * max_file_size_mb * 1024 * 1024)); // 磁盘最小预留空间10MB
    
    fileSink->set_formatter(fmt);
    fileSink->locked_backend()->scan_for_files();
    fileSink->locked_backend()->auto_flush(true);
    boost::log::core::get()->add_sink(fileSink);
  }

  void Logger::AddConsoleSink(boost::log::formatter fmt) {
    auto consoleSink = boost::log::add_console_log();
    consoleSink->set_formatter(fmt);
    boost::log::core::get()->add_sink(consoleSink);
  }

  void Logger::SetLvl(Lvl lvl) {
    auto slvl = static_cast<int>(lvl);
    boost::log::core::get()->set_filter(trivial::severity >= lvl);
  }

} // namespace lob
} // namespace cpplib
