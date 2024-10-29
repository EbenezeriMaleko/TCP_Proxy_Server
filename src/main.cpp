// src/main.cpp
#include "TCPProxyServer.h"
#include "Logger.h"
#include <iostream>

int main() {
    const int thread_count = 5;
    io_context io_context;
    unsigned short port = 8000;

    Logger logger("tcp_proxy_server.log");
    TCPProxyServer server(io_context, port, thread_count, logger);

    std::cout << "Starting TCP Proxy Server on Port " << port << "..." << std::endl;
    server.start();
    return 0;
}
