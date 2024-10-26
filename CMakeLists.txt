cmake_minimum_required(VERSION 3.10)
project(TCPProxyServer)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED COMPONENTS system)

add_executable(tcp_proxy_server src/main.cpp)
target_link_libraries(tcp_proxy_server Boost::system pthread)

