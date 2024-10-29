#include "Logger.h"

Logger::Logger(const std::string& filename) : log_file_(filename, std::ios_base::app) {
    if (!log_file_.is_open()) {
        std::cerr << "Error: Unable to open log file!" << std::endl;
    }
}

void Logger::log_message(const std::string& message) {
    std::lock_guard<std::mutex> lock(log_mutex_);

    // Log to console
    std::cout << message << std::endl;

    // Log to file
    if (log_file_.is_open()) {
        log_file_ << message << std::endl;
    }
}
