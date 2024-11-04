cmake_minimum_required(VERSION 3.10)
project(LogFileProcessor)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Find and link SQLite3 (required for logging to SQLite database)
find_package(SQLite3 REQUIRED)

# Source files
set(SOURCES
    src/main.cpp
    src/logger_processor.cpp
    src/logger.cpp
)
# Add the executable
add_executable(log_processor ${SOURCES})

# Link libraries
target_link_libraries(log_processor SQLite::SQLite3)
