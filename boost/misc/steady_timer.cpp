#include <iostream>
#include <chrono>
#include <thread>

#include <boost/asio/io_service.hpp>
#include <boost/asio/steady_timer.hpp>

using namespace std;
using namespace boost::asio;

chrono::time_point<chrono::high_resolution_clock> start;

int main() {
  io_service io1;
  io_service io2;

  start = chrono::high_resolution_clock::now();

  steady_timer timer1{io1, chrono::seconds{3}};
  timer1.async_wait([](const boost::system::error_code& ec) {
    auto stop = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = stop - start;
    cout << "Timer1: " << elapsed.count() << endl; } );

  steady_timer timer2{io2, chrono::seconds{3}};
  timer2.async_wait([](const boost::system::error_code& ec) {
    auto stop = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = stop - start;
    cout << "Timer2: " << elapsed.count() << endl; } );

  thread thread1{[&io1](){ io1.run(); }};
  thread thread2{[&io2](){ io2.run(); }};

  thread1.join();
  thread2.join();

  return 0;
}
