#include <boost/asio/io_service.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/ip/tcp.hpp>

#include <iostream>
#include <string>
#include <array>

using namespace std;
using namespace boost::asio;
using namespace boost::asio::ip;

io_service io;
tcp::resolver resolv{io};
tcp::socket tcp_socket{io};
array<char, 4096> bytes;

void read_handler(const boost::system::error_code& ec,
                  size_t bytes_transferred) {
  if (!ec) {
    cout.write(bytes.data(), bytes_transferred);
    tcp_socket.async_read_some(buffer(bytes), read_handler);
  }
}

void connect_handler(const boost::system::error_code& ec) {
  if (!ec) {
    string r = "GET / HTTP/1.1\r\nHost: theboostcpplibraries.com\r\n\r\n";
    write(tcp_socket, buffer(r));
    tcp_socket.async_read_some(buffer(bytes), read_handler);
  }
}

void resolve_handler(const boost::system::error_code& ec,
                     tcp::resolver::iterator it) {
  if (!ec)
    tcp_socket.async_connect(*it, connect_handler);
}

int main() {
  tcp::resolver::query q{"theboostcpplibraries.com", "80"};
  resolv.async_resolve(q, resolve_handler);
  io.run();
}
