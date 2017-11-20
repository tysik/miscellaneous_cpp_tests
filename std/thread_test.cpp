#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <algorithm>
#include <mutex>
#include <atomic>

using namespace std;

const size_t num_threads = 10;
const size_t vector_size = 1000;

mutex barrier;

void call_from_thread(int a)
{
  cout << "Started thread: " << a << endl;
}

void my_dot(const vector<int> &v1, const vector<int> &v2, long long &result, size_t left, size_t right)
{
  for (size_t i = left; i < right; ++i)
    result += v1[i] * v2[i];
}

void mutex_dot(const vector<int> &v1, const vector<int> &v2, long long &result, size_t left, size_t right)
{
  int local_result = 0;
  for (size_t i = left; i < right; ++i)
    local_result += v1[i] * v2[i];

  //lock_guard<mutex> block_thread(barrier);
  barrier.lock();
  result += local_result;
  barrier.unlock();
}

void atomic_dot(const vector<int> &v1, const vector<int> &v2, atomic<long long> &result, size_t left, size_t right)
{
  int local_result = 0;
  for (size_t i = left; i < right; ++i)
    local_result += v1[i] * v2[i];

  result += local_result;
}

class SayHello
{
public:
  void sayHello(const string &name)
  {
    cout << "Hello " << name << endl;
  }
};

int main()
{
  vector<int> v1(vector_size, 1);
  vector<int> v2(vector_size, 2);

  iota(v1.begin(), v1.end(), 1);
  iota(v2.begin(), v2.end(), 2);

  for_each(v1.begin(), v1.end(), [](int a){ cout << a << " "; });
  cout << endl;
  for_each(v2.begin(), v2.end(), [](int a){ cout << a << " "; });

  cout << endl;

  long long result = 0;

  thread my_thread(my_dot, std::ref(v1), std::ref(v2), std::ref(result), 0, vector_size);
  my_thread.join();

  cout << "Single thread result: " << result << endl;
  result = 0;

  vector<thread> threads;

  for (size_t i = 0; i < num_threads; ++i)
    threads.push_back(thread(call_from_thread, i));

  for (auto &t : threads)
    t.join();

  cout << endl;

  threads.clear();

  for (size_t i = 0; i < num_threads; ++i)
    threads.push_back(thread(mutex_dot, std::cref(v1), std::cref(v2), std::ref(result), i * vector_size / num_threads, (i+1) * vector_size / num_threads));

  for (auto &t : threads)
    t.join();

  cout << "Mutexed threads result: " << result << endl;

  threads.clear();

  atomic<long long> atomic_result(0);

  for (size_t i = 0; i < num_threads; ++i)
    threads.push_back(thread(atomic_dot, std::cref(v1), std::cref(v2), std::ref(atomic_result), i * vector_size / num_threads, (i+1) * vector_size / num_threads));

  for (auto &t : threads)
    t.join();

  cout << "Atomicized threads result: " << atomic_result << endl;

  // Using a non-static member function of an object
  SayHello sh;
  thread ts(&SayHello::sayHello, &sh, "Matt");
  ts.join();

  // Using lambda
  thread tl([](const string &name){ cout << "Hello " << name << endl; }, "Tom");
  tl.join();

  return 0;
}
