#include <boost/thread.hpp>
#include <boost/thread/scoped_thread.hpp>
#include <boost/chrono.hpp>

#include <iostream>

void wait(int seconds)
{
  boost::this_thread::sleep_for(boost::chrono::seconds{seconds});
}

boost::mutex mutex;

void thread()
{
  using boost::this_thread::get_id;

  for (int i = 0; i < 3; ++i)
  {
    wait(1);
//    mutex.lock();
    boost::lock_guard<boost::mutex> lock{mutex};
    std::cout << "Thread " << get_id() << ": " << i << std::endl;
//    mutex.unlock();
  }
}

void thr1()
{
  using boost::this_thread::get_id;

  for (int i = 0; i < 3; ++i)
  {
    wait(1);
//    boost::unique_lock<boost::timed_mutex> lock{mutex};
    std::cout << "Thread " << get_id() << ": " << i << std::endl;
//    boost::timed_mutex *m = lock.release();
//    m->unlock();
  }
}

void thr2()
{
  using boost::this_thread::get_id;

  for (int i = 0; i < 3; ++i)
  {
    wait(1);
//    boost::unique_lock<boost::timed_mutex> lock{mutex, boost::try_to_lock};
//    if (lock.owns_lock() || lock.try_lock_for(boost::chrono::seconds{1}))
    {
      std::cout << "Thread " << get_id() << ": " << i << std::endl;
    }
  }
}

int main()
{
  boost::thread t1{thread};
  boost::thread t2{thread};

  t1.join();
  t2.join();

  boost::thread t3{thr1};
  boost::thread t4{thr2};

  t3.join();
  t4.join();
}
