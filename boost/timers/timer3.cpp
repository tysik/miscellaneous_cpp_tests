#include <iostream>
#include <chrono>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;
using namespace std::chrono;

high_resolution_clock::time_point start, stop;

void print(const boost::system::error_code& ec, boost::asio::deadline_timer* t, int* count) {
  if (*count <= 5) {
    cout << *count << " : ";
    ++(*count);

    stop = high_resolution_clock::now();
    duration<double> elapsed = duration_cast<duration<double>>(stop - start);
    cout << elapsed.count() << endl;

    t->expires_at(t->expires_at() + boost::posix_time::seconds(1));
    t->async_wait(boost::bind(print, boost::asio::placeholders::error, t, count));
  }
}

int main() {
  boost::asio::io_service io;

  start = high_resolution_clock::now();

  int count = 1;
  boost::asio::deadline_timer timer(io, boost::posix_time::seconds(1));
  timer.async_wait(boost::bind(print, boost::asio::placeholders::error, &timer, &count));

  io.run();

  return 0;
}
