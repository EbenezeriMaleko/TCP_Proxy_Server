#include <iostream>
#include <fstream>
#include <string>
#include "logger.h"
#include "logger_processor.h"

int main() {
    const std::string logFileName = "/media/ebenezeri/_dev_sda6/Software_assesment/qubitech_interview/log_processor/data/large_log.txt"; // Adjust path as necessary
    Logger logger("logs.db");

    std::ifstream logFile(logFileName);
    if (!logFile.is_open()) {
        std::cerr << "Error opening log file at: " << logFileName << std::endl;
        return 1;
    }

    std::cout << "Log file opened successfully." << std::endl;

    // Process log lines in a multi-threaded manner
    processLogLines(logFile, logger);

    logFile.close();
    return 0;
}
