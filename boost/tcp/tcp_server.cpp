#include <ctime>
#include <iostream>
#include <string>

#include <boost/asio.hpp>

using namespace std;
using boost::asio::ip::tcp;

string makeDaytimeString() {
  time_t now = time(0);
  return ctime(&now);
}

int main() {
  try {
    boost::asio::io_service io;

    tcp::acceptor acceptor(io, tcp::endpoint(tcp::v4(), 32167));

    while (true) {
      tcp::socket socket(io);
      acceptor.accept(socket);  // Blocking - wait for the client

      string message = makeDaytimeString();
      boost::system::error_code ec;
      boost::asio::write(socket, boost::asio::buffer(message), ec);
    }
  }
  catch (exception& e) {
    cerr << e.what() << endl;
  }

  return 0;
}
