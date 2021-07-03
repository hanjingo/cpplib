#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <memory>

#include <boost/filesystem.hpp>

#define B  1
#define KB 1024 * B
#define MB 1024 * KB
#define GB 1024 * MB
#define TB 1024 * GB

namespace cpplib {
namespace util {

namespace fs = boost::filesystem;

// 判断路径是否存在
static inline bool IsExist(const std::string& abspath) { return fs::exists(abspath); };

// 返回当前路径
static inline std::shared_ptr<std::string> Pwd() { return std::make_shared<std::string>(fs::current_path().string()); };

// 拆分路径
static inline void Split(const std::string& file_path_name, 
                         std::string& path, 
                         std::string& file_name) {
  fs::path p(file_path_name);
  path      = p.parent_path().string();
  file_name = p.filename().string();
};

// 强行创建路径
static inline bool MustCreatePath(const std::string& path) { 
  return fs::create_directories(fs::path(path)); 
};

// 查找所有子目录
static void SubDirs(std::vector<std::string>& out, 
                    const std::string& path, 
                    int depth = 1) {
  fs::path                         root(path);
  fs::recursive_directory_iterator end;
  for (fs::recursive_directory_iterator itr(root); itr != end; itr++) {
    if (!fs::is_directory(*itr)) 
      itr.pop();     // 跳出当前目录

    if (itr.level() > depth) {
      itr.no_push(); // 跳出整个目录
      out.push_back(itr->path().string());
    }
  }
};

// 强行创建文件
static bool MustCreateFile(const std::string& file_path_name) {
  std::string path{};
  std::string file_name{};
  cpplib::util::Split(file_path_name, path, file_name);
  if (!cpplib::util::MustCreatePath(path))
    return false;
  std::ofstream f;
  f.open(file_name);
  f.close();
  return true;
};

} // namespace cpplib
} // namespace utils
