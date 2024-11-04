# Minimum CMake version requirement
cmake_minimum_required(VERSION 3.10)

# Set policy for Boost module compatibility
if(POLICY CMP0167)
    cmake_policy(SET CMP0167 OLD)
endif()

# Project name and version
project(TCPProxyServer VERSION 1.0)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find Boost library
find_package(Boost REQUIRED COMPONENTS system)

# Specify the source file
set(SOURCES src/main.cpp src/Logger.cpp src/TCPProxyServer.cpp)

# Add the include directory to the include path
include_directories(include)  # Adjusted to point to the 'include' folder

# Add the executable target for the project
add_executable(tcp_proxy_server ${SOURCES})

# Include Boost headers and link Boost libraries
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(tcp_proxy_server Boost::system pthread)
endif()

# Output project configuration summary
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "Version: ${PROJECT_VERSION}")
message(STATUS "Boost Found: ${Boost_FOUND}")
message(STATUS "Boost Include Dirs: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost Libraries: ${Boost_LIBRARIES}")
