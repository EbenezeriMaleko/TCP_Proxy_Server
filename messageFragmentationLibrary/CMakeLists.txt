# CMakeLists.txt

cmake_minimum_required(VERSION 3.10)
project(MessageFragmentationLibrary)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Source files
set(SOURCES
    src/main.cpp
    src/MessageFragmenter.cpp
    src/MessageAssembler.cpp
)

# Create the executable
add_executable(message_fragmentation ${SOURCES})
