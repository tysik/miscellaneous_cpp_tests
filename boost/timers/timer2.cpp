#include <iostream>
#include <chrono>

#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;
using namespace std::chrono;

high_resolution_clock::time_point start, stop;

void print(const boost::system::error_code& ec) {
  stop = high_resolution_clock::now();

  duration<double> elapsed = duration_cast<duration<double>>(stop - start);

  cout << elapsed.count() << endl;
}

int main() {
  boost::asio::io_service io;

  start = high_resolution_clock::now();

  boost::asio::deadline_timer timer(io, boost::posix_time::seconds(5));
  timer.async_wait(&print);

  io.run();

  return 0;
}
