#include <iostream>

#include <boost/array.hpp>
#include <boost/asio.hpp>

using namespace std;
using boost::asio::ip::udp;

int main(int argc, char* argv[]) {
  try {
    if (argc != 2) {
      cerr << "Usage: client <host>" << endl;
      return 1;
    }

    boost::asio::io_service io;

    udp::resolver resolver(io);
    udp::resolver::query query(udp::v4(), argv[1], "32167");

    udp::endpoint receiver_endpoint = *resolver.resolve(query);

    udp::socket socket(io);
    socket.open(udp::v4());

    boost::array<char, 1> send_buf = {{ 0 }};
    socket.send_to(boost::asio::buffer(send_buf), receiver_endpoint);

    boost::array<char, 128> receive_buf;
    udp::endpoint sender_endpoint;
    size_t len = socket.receive_from(boost::asio::buffer(receive_buf), sender_endpoint);

    cout.write(receive_buf.data(), len);
  }
  catch (exception& e) {
    cout << e.what() << endl;
  }

  return 0;
}
