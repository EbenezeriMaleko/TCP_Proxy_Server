# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(TCPProxyServer)

#Set the CMP0167 policy
cmake_policy(SET CMP0167 NEW)

# Use C++17 standard
set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(include)

# Boost Asio requires linking to pthread
find_package(Boost REQUIRED)
find_package(Threads REQUIRED)

# Source files
add_executable(TCPProxyServer src/main.cpp src/TCPProxyServer.cpp src/Logger.cpp)

# Link libraries
target_link_libraries(TCPProxyServer Boost::boost Threads::Threads)

