#include <boost/asio.hpp>
#include <iostream>
#include <thread>
#include <vector>
#include <fstream>
#include <mutex>

using namespace boost::asio;
using ip::tcp;

class TCPProxyServer {
public:
    TCPProxyServer(io_context& io_context, unsigned short port, int thread_count)
        : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)), io_context_(io_context), thread_count_(thread_count) {
        if (!acceptor_.is_open()) {
                std::cerr << "Error Could not open acceptor. " << std::endl;
        }
    }

    void start() {
        accept_connections();

        for (int i = 0; i < thread_count_; i++) {
            threads_.emplace_back([&]() { io_context_.run(); });
        }

        for (auto& thread : threads_) {
            thread.join();
        }
    }

private:
    void log_message(const std::string& message){
        std::cout <<message <<std::endl;
    }

    void accept_connections() {
        auto socket = std::make_shared<tcp::socket>(io_context_);
        acceptor_.async_accept(*socket, [this, socket](boost::system::error_code ec) {
            if (!ec) {
                std::cout << "Accepted connection" << std::endl;
                handle_client(socket);
            }
            accept_connections();  // Continue accepting new connections
        });
    }

    void handle_client(std::shared_ptr<tcp::socket>socket) {
        auto buffer = std::make_shared<std::array<char, 1024>>();

        socket->async_read_some(boost::asio::buffer(*buffer),
        [this, socket, buffer](boost::system::error_code ec, std::size_t bytes_transferred){
            if(!ec){
                log_message("Received data: " + std::string(buffer->data(), bytes_transferred));

                std::string response = "HTTP/1.0 200 OK\r\n"
                                       "Content-Type: text/plain\r\n"
                                       "\r\n"
                                       "Hello, world";

                async_write(*socket, boost::asio::buffer(response), [socket](boost::system::error_code, std::size_t){});

                handle_client(socket);
            }else{
                std::cerr <<"Error: "<< ec.message() << std::endl;
            }
        });
    }

    tcp::acceptor acceptor_;
    io_context& io_context_;
    int thread_count_;
    std::vector<std::thread> threads_;  // Declare the threads vector
};

int main() {
    const int thread_count = 5;
    io_context io_context;
    unsigned short port = 8000;

    TCPProxyServer server(io_context, port, thread_count);
    std::cout << "Starting TCP Proxy Server on Port " << port << "..." << std::endl;
    server.start();
    return 0;    
}
