#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <mutex>
#include <thread>

class Logger {
public:
    Logger(const std::string& filename);
    void log_message(const std::string& message);

private:
    std::ofstream log_file_;
    std::mutex log_mutex_;
};
