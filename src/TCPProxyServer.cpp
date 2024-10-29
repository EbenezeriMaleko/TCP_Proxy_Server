#include "TCPProxyServer.h"

TCPProxyServer::TCPProxyServer(io_context& io_context, unsigned short port, int thread_count, Logger& logger)
    : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)), io_context_(io_context), thread_count_(thread_count), logger_(logger) {
    if (!acceptor_.is_open()) {
        logger_.log_message("Error: Could not open acceptor.");
    }
}

void TCPProxyServer::start() {
    accept_connections();

    for (int i = 0; i < thread_count_; i++) {
        int thread_number = i + 1;  // Thread number from 1 to thread_count_
        threads_.emplace_back([&, thread_number]() { 
            try {
                io_context_.run();
            }
            catch(const std::exception& e) {
                log_with_thread(thread_number, "Exception in thread: " + std::string(e.what()));
            }
        });
    }

    for (auto& thread : threads_) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}

void TCPProxyServer::accept_connections() {
    auto socket = std::make_shared<tcp::socket>(io_context_);
    acceptor_.async_accept(*socket, [this, socket](boost::system::error_code ec) {
        if (!ec) {
            logger_.log_message("Accepted connection");
            handle_client(socket, 1);  // Start with thread 1 by default
        }
        accept_connections();  // Continue accepting new connections
    });
}

void TCPProxyServer::handle_client(std::shared_ptr<tcp::socket> socket, int thread_number) {
    auto buffer = std::make_shared<std::array<char, 1024>>();

    socket->async_read_some(boost::asio::buffer(*buffer),
    [this, socket, buffer, thread_number](boost::system::error_code ec, std::size_t bytes_transferred) {
        if (!ec) {
            log_with_thread(thread_number, "Received data: " + std::string(buffer->data(), bytes_transferred));

            std::string response = "HTTP/1.0 200 OK\r\n"
                                   "Content-Type: text/plain\r\n"
                                   "\r\n"
                                   "Hello, world\r\n";

            async_write(*socket, boost::asio::buffer(response), [socket, thread_number, this](boost::system::error_code write_ec, std::size_t) {
                if (!write_ec) {
                    socket->shutdown(tcp::socket::shutdown_send);
                    socket->close();
                } else {
                    log_with_thread(thread_number, "Error in write: " + write_ec.message());
                }
            });

            handle_client(socket, thread_number);  // Continue handling with the same thread number
        } else {
            log_with_thread(thread_number, "Error: " + ec.message());
        }
    });
}

// Helper function to log with thread number
void TCPProxyServer::log_with_thread(int thread_number, const std::string& message) {
    logger_.log_message("[Thread " + std::to_string(thread_number) + "] " + message);
}
