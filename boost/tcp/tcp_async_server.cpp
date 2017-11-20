#include <ctime>
#include <iostream>
#include <string>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

using namespace std;
using boost::asio::ip::tcp;

string makeDaytimeString() {
  time_t now = time(0);
  return ctime(&now);
}

class tcp_connection : public boost::enable_shared_from_this<tcp_connection> {
public:
  typedef boost::shared_ptr<tcp_connection> pointer;

  tcp_connection(boost::asio::io_service& io_service)
    : socket_(io_service) {
    cout << "Connection constructor" << endl;
  }

  static pointer create(boost::asio::io_service& io_service) {
    return pointer(new tcp_connection(io_service));
  }

  tcp::socket& socket() {
    return socket_;
  }

  void start() {
    cout << "Sending message" << endl;

    message_ = makeDaytimeString();
//    boost::asio::async_write(socket_, boost::asio::buffer(message_),
//                             boost::bind(&tcp_connection::handle_write, shared_from_this(),
//                                         boost::asio::placeholders::error(),
//                                         boost::asio::placeholders::bytes_transferred));
    boost::asio::async_write(socket_, boost::asio::buffer(message_),
                             boost::bind(&tcp_connection::handle_write, shared_from_this()));
  }

private:
//  void handle_write(const boost::system::error_code& e, size_t len) {
//    cout << "Sent " << len << " bytes" << endl;
//  }
  void handle_write() {
    cout << "Sent date" << endl;
  }

  tcp::socket socket_;
  string message_;
};




class tcp_server {
public:
  tcp_server(boost::asio::io_service& io_service)
    : acceptor_(io_service, tcp::endpoint(tcp::v4(), 32167))
  {
    cout << "Server constructor" << endl;
    start_accept();
  }

private:
  void start_accept() {
    cout << "Waiting for connection" << endl;

    tcp_connection::pointer new_connection = tcp_connection::create(acceptor_.get_io_service());
    acceptor_.async_accept(new_connection->socket(),
                           boost::bind(&tcp_server::handle_accept, this, new_connection,
                                       boost::asio::placeholders::error));
  }

  void handle_accept(tcp_connection::pointer new_connection,
      const boost::system::error_code& error) {

    cout << "Handling acception..." << endl;

    if (!error) {
      new_connection->start();
    }

    cout << "...and starting listening for next connection in the background" << endl;
    start_accept();
  }

  tcp::acceptor acceptor_;
};

int main() {
  try {
    boost::asio::io_service io_service;
    tcp_server server(io_service);

    cout << "Started the server in the background" << endl;

    io_service.run();
  }
  catch (exception& e) {
    cout << e.what() << endl;
  }

  return 0;
}
