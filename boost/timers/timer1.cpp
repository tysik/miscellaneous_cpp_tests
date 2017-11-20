#include <iostream>
#include <chrono>

#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;
using namespace std::chrono;

int main() {
  boost::asio::io_service io;

  auto start = high_resolution_clock::now();

  boost::asio::deadline_timer timer(io, boost::posix_time::seconds(5));
  timer.wait();

  auto stop = high_resolution_clock::now();

  duration<double> elapsed = stop - start;
  cout << elapsed.count() << endl;

  return 0;
}
