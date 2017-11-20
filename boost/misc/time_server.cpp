#include <boost/asio/io_service.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/ip/tcp.hpp>

#include <iostream>
#include <string>
#include <ctime>

using namespace std;
using namespace boost::asio;
using namespace boost::asio::ip;

io_service io;
tcp::endpoint tcp_endpoint{tcp::v4(), 32167};
tcp::acceptor tcp_acceptor{io, tcp_endpoint};
tcp::socket tcp_socket{io};
string data;

void write_handler(const boost::system::error_code& ec, size_t bytes_transferred) {
  if (!ec)
    tcp_socket.shutdown(tcp::socket::shutdown_send);
}

void accept_handler(const boost::system::error_code& ec) {
  if (!ec) {
    time_t now = time(nullptr);
    data = ctime(&now);
    async_write(tcp_socket, buffer(data), write_handler);
  }
}

int main() {
  tcp_acceptor.listen();
  tcp_acceptor.async_accept(tcp_socket, accept_handler);
  io.run();
}
