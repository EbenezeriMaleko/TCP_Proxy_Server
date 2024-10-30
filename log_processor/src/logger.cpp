#include "logger.h"
#include <iostream>
#include <sqlite3.h> // Ensure you include sqlite3.h

Logger::Logger(const std::string& dbName) {
    if (sqlite3_open(dbName.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Error: Failed to connect to database: " << sqlite3_errmsg(db) << std::endl;
    } else {
        // Create logs table if it doesn't exist
        const char* createTableSQL = R"(
            CREATE TABLE IF NOT EXISTS logs (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                message TEXT NOT NULL
            );
        )";

        char* errMsg = nullptr;
        if (sqlite3_exec(db, createTableSQL, nullptr, nullptr, &errMsg) != SQLITE_OK) {
            std::cerr << "Error: Failed to create table: " << errMsg << std::endl;
            sqlite3_free(errMsg);
        }
    }
}

Logger::~Logger() {
    if (db) {
        sqlite3_close(db);
    }
}

void Logger::logMessage(const std::string& message) {
    // Prepare the SQL statement to insert the log message
    const char* insertSQL = "INSERT INTO logs (message) VALUES (?);";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, insertSQL, -1, &stmt, nullptr) == SQLITE_OK) {
        // Bind the message to the SQL statement
        sqlite3_bind_text(stmt, 1, message.c_str(), -1, SQLITE_STATIC);
        
        // Execute the SQL statement
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << "Error: Failed to insert message: " << sqlite3_errmsg(db) << std::endl;
        }

        // Finalize the statement to release resources
        sqlite3_finalize(stmt);
    } else {
        std::cerr << "Error: Failed to prepare SQL statement: " << sqlite3_errmsg(db) << std::endl;
    }

    std::cout << "Logging message: " << message << std::endl; // Debug output
}
