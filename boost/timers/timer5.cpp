#include <iostream>
#include <chrono>

#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;
using namespace std::chrono;

class Printer {
public:
  Printer(boost::asio::io_service& io)
    : strand_(io),
      timer1_(io, boost::posix_time::seconds(1)),
      timer2_(io, boost::posix_time::seconds(1)),
      count_(1)
  {
    timer1_.async_wait(strand_.wrap(boost::bind(&Printer::print1, this)));
    timer2_.async_wait(strand_.wrap(boost::bind(&Printer::print2, this)));
    start_ = high_resolution_clock::now();
  }

  ~Printer() {
    stop_ = high_resolution_clock::now();
    duration<double> elapsed = duration_cast<duration<double>>(stop_ - start_);
    cout << count_ << " : " << elapsed.count() << endl;
  }

  void print1() {
    if (count_ <= 10) {
      cout << "Timer 1 : " << count_ << " : ";
      ++count_;

      stop_ = high_resolution_clock::now();
      duration<double> elapsed = duration_cast<duration<double>>(stop_ - start_);
      cout << elapsed.count() << endl;

      timer1_.expires_at(timer1_.expires_at() + boost::posix_time::seconds(1));
      timer1_.async_wait(strand_.wrap(boost::bind(&Printer::print1, this)));
    }
  }

  void print2() {
    if (count_ <= 15) {
      cout << "Timer 2 : " << count_ << " : ";
      ++count_;

      stop_ = high_resolution_clock::now();
      duration<double> elapsed = duration_cast<duration<double>>(stop_ - start_);
      cout << elapsed.count() << endl;

      timer2_.expires_at(timer2_.expires_at() + boost::posix_time::seconds(1));
      timer2_.async_wait(strand_.wrap(boost::bind(&Printer::print2, this)));
    }
  }

private:
  high_resolution_clock::time_point start_, stop_;
  boost::asio::strand strand_;
  boost::asio::deadline_timer timer1_;
  boost::asio::deadline_timer timer2_;
  int count_;
};


int main() {
  boost::asio::io_service io;
  Printer p(io);

  boost::thread t(boost::bind(&boost::asio::io_service::run, &io));
  io.run();
  t.join();

  return 0;
}
