#include <iostream>
#include <chrono>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;
using namespace std::chrono;

class Printer {
public:
  Printer(boost::asio::io_service& io)
    : timer_(io, boost::posix_time::seconds(1)),
      count_(1)
  {
    timer_.async_wait(boost::bind(&Printer::print, this));
    start_ = high_resolution_clock::now();
  }

  ~Printer() {
    stop_ = high_resolution_clock::now();
    duration<double> elapsed = duration_cast<duration<double>>(stop_ - start_);
    cout << count_ << " : " << elapsed.count() << endl;
  }

  void print() {
    if (count_ <= 5) {
      cout << count_ << " : ";
      ++count_;

      stop_ = high_resolution_clock::now();
      duration<double> elapsed = duration_cast<duration<double>>(stop_ - start_);
      cout << elapsed.count() << endl;

      timer_.expires_at(timer_.expires_at() + boost::posix_time::seconds(1));
      timer_.async_wait(boost::bind(&Printer::print, this));
    }
  }

private:
  high_resolution_clock::time_point start_, stop_;
  boost::asio::deadline_timer timer_;
  int count_;
};


int main() {
  boost::asio::io_service io;
  Printer p(io);
  io.run();

  return 0;
}
