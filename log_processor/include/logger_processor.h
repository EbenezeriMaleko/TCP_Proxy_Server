#ifndef LOGGER_PROCESSOR_H
#define LOGGER_PROCESSOR_H

#include <fstream>
class Logger; // Forward declaration of Logger class

void processLogLines(std::ifstream& logFile, Logger& logger);

#endif // LOGGER_PROCESSOR_H
