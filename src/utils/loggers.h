#include <fstream>
#include <mutex>
#include <string>
#include "utils/singleton.h"

namespace blackjack {

class Logger : public Singleton<Logger> {
  enum LogLevel {
    INFO,
    WARNING,
    ERROR,
  };

 public:
  void init(const std::string& filename = "");
  void info(const std::string& message);
  void warning(const std::string& message);
  void error(const std::string& message);

 private:
  std::ofstream file_stream;
  bool is_initialized = false;
  std::mutex init_mutex;

  // Call inside of init since we want it to be singleton.
  ~Logger();

  void log(LogLevel level, std::string message);
  std::string format_log(LogLevel level, const std::string& message);

  // Grant Singleton access to private constructor/destructor
  friend class Singleton<Logger>;
};
}  // namespace blackjack
