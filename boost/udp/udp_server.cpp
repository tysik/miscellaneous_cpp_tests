#include <iostream>
#include <string>
#include <ctime>

#include <boost/array.hpp>
#include <boost/asio.hpp>

using namespace std;
using boost::asio::ip::udp;

string makeDaytimeString() {
  time_t now = time(0);
  return ctime(&now);
}

int main() {
  try {
    boost::asio::io_service io;

    udp::socket socket(io, udp::endpoint(udp::v4(), 32167));

    while (true) {
      boost::array<char, 1> recv_buf;
      udp::endpoint remote_endpoint;
      boost::system::error_code error;
      socket.receive_from(boost::asio::buffer(recv_buf), remote_endpoint, 0, error);

      if (error && error != boost::asio::error::message_size)
        throw boost::system::system_error(error);

      string message = makeDaytimeString();
      boost::system::error_code dummy_error;
      socket.send_to(boost::asio::buffer(message), remote_endpoint, 0, dummy_error);
    }

  }
  catch (exception& e) {
    cerr << e.what() << endl;
  }

  return 0;
}
