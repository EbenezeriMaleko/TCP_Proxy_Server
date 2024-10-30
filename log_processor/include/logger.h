#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <sqlite3.h>

class Logger {
public:
    Logger(const std::string& dbName);
    ~Logger();
    void logMessage(const std::string& message);
private:
    sqlite3* db;
};

#endif // LOGGER_H
