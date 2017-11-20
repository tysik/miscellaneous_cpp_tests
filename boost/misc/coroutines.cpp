#include <boost/asio/io_service.hpp>
#include <boost/asio/spawn.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/ip/tcp.hpp>

#include <list>
#include <string>
#include <ctime>

using namespace boost::asio;
using namespace boost::asio::ip;

io_service io;
tcp::endpoint tcp_endpoint{tcp::v4(), 32167};
tcp::acceptor tcp_acceptor{io, tcp_endpoint};
std::list<tcp::socket> tcp_sockets;

void do_write(tcp::socket& tcp_socket, yield_context yield)
{
  std::time_t now = std::time(nullptr);
  std::string data = std::ctime(&now);
  async_write(tcp_socket, buffer(data), yield);
  tcp_socket.shutdown(tcp::socket::shutdown_send);
}

void do_accept(yield_context yield)
{

  for (int i = 0; i < 2; ++i)
  {
    tcp_sockets.emplace_back(io); // To create socket right in place (without copying)
    tcp_acceptor.async_accept(tcp_sockets.back(), yield);
    spawn(io, [](yield_context yield){ do_write(tcp_sockets.back(), yield); });
  }
}

int main()
{
  tcp_acceptor.listen();
  spawn(io, do_accept);
  io.run();
}
