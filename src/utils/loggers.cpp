#include "./loggers.h"
#include <iostream>
#include <mutex>

namespace blackjack {

void Logger::init(const std::string& filename) {
  std::lock_guard<std::mutex> lock(init_mutex);
  if (is_initialized) {
    return;
  }

  if (!filename.empty()) {
    file_stream.open(filename, std::ios::out | std::ios::app);
    if (!file_stream.is_open()) {
      std::cerr << "[ERROR] Failed to open log file: " << filename << std::endl;
    }
  }
  is_initialized = true;
}

Logger::~Logger() {
  if (file_stream.is_open()) {
    file_stream.close();
  }
}

void Logger::info(const std::string& message) {
  log(Logger::LogLevel::INFO, message);
}

void Logger::error(const std::string& message) {
  log(Logger::LogLevel::ERROR, message);
}

void Logger::warning(const std::string& message) {
  log(Logger::LogLevel::WARNING, message);
}

void Logger::log(LogLevel level, std::string message) {
  if (!is_initialized) {
    std::cerr << "[ERROR] Logger not initialized. get().init() first."
              << std::endl;
    return;
  }
  std::string log_message = format_log(level, message);
  std::cout << log_message << "\n";

  if (file_stream.is_open()) {
    file_stream << log_message << std::endl;
  }
}

std::string Logger::format_log(LogLevel level, const std::string& message) {
  std::string level_str;
  switch (level) {
    case LogLevel::INFO:
      level_str = "[INFO]\t";
      break;
    case LogLevel::WARNING:
      level_str = "[WARNING]\t";
      break;
    case LogLevel::ERROR:
      level_str = "[ERROR]\t";
      break;
  }
  return level_str + message;
}

}  // namespace blackjack
