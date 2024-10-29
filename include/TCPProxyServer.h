#pragma once
#include <boost/asio.hpp>
#include <vector>
#include <memory>
#include <thread>
#include "Logger.h"

using namespace boost::asio;
using ip::tcp;

class TCPProxyServer {
public:
    TCPProxyServer(io_context& io_context, unsigned short port, int thread_count, Logger& logger);
    void start();

private:
    void accept_connections();
    void handle_client(std::shared_ptr<tcp::socket> socket, int thread_number);
    void log_with_thread(int thread_number, const std::string& message);

    tcp::acceptor acceptor_;
    io_context& io_context_;
    int thread_count_;
    std::vector<std::thread> threads_;
    Logger& logger_;  // Reference to logger for logging messages
};
