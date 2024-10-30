#include <fstream>
#include <string>
#include <thread>
#include <vector>
#include "logger.h"
#include "logger_processor.h"

// Function to process a single log line
void processSingleLine(const std::string& line, Logger& logger) {
    // Simulate processing (replace with actual processing logic)
    std::string processedLine = "Processed: " + line;
    logger.logMessage(processedLine); // Log to database
}

// Function to process log lines from the file
void processLogLines(std::ifstream& logFile, Logger& logger) {
    std::string line;
    std::vector<std::thread> threads; // Vector to hold threads

    // Read each line from the log file
    while (std::getline(logFile, line)) {
        if (!line.empty()) { // Ensure the line is not empty before processing
            threads.emplace_back(processSingleLine, line, std::ref(logger)); // Create a thread for processing the line
        }
    }

    // Join all threads to ensure completion before exiting
    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join(); // Wait for each thread to finish
        }
    }
}
