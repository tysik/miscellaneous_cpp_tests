#include <iostream>

#include <boost/array.hpp>
#include <boost/asio.hpp>

using namespace std;
using boost::asio::ip::tcp;

int main(int argc, char* argv[]) {
  try {
    if (argc != 2) {
      cerr << "Usage: client <host>" << endl;
      return 1;
    }

    boost::asio::io_service io;

    tcp::resolver resolver(io);

    tcp::resolver::query query(argv[1], "32167"); // "daytime" stands for port 13

    tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

    tcp::socket socket(io);
    boost::asio::connect(socket, endpoint_iterator);

    while (true) {
      boost::array<char, 128> buffer;
      boost::system::error_code error;

      size_t len = socket.read_some(boost::asio::buffer(buffer), error);

      if (error == boost::asio::error::eof)
        break;
      else if (error)
        throw boost::system::system_error(error);

      cout.write(buffer.data(), len);
    }
  }
  catch (exception& e) {
    cerr << e.what() << endl;
  }

  return 0;
}
