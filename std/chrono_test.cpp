#include <iostream>
#include <chrono>
#include <typeinfo>

using namespace std;

long fibonacci(unsigned n)
{
    if (n < 2) return n;
    return fibonacci(n-1) + fibonacci(n-2);
}

int main()
{
  cout << "system_clock period: ";
  cout << chrono::system_clock::period::num << " / ";
  cout << chrono::system_clock::period::den << " seconds. ";
  cout << "Steady = " << boolalpha << chrono::system_clock::is_steady << endl;

  cout << "system_clock period: ";
  cout << chrono::high_resolution_clock::period::num << " / ";
  cout << chrono::high_resolution_clock::period::den << " seconds. ";
  cout << "Steady = " << boolalpha << chrono::high_resolution_clock::is_steady << endl;

  cout << "system_clock period: ";
  cout << chrono::steady_clock::period::num << " / ";
  cout << chrono::steady_clock::period::den << " seconds. ";
  cout << "Steady = " << boolalpha << chrono::steady_clock::is_steady << endl;

  cout << endl;

  auto tic = chrono::steady_clock::now(); // Here auto stands for chrono::steady_clock::time_point
  cout << "Fibonacci(42) = " << fibonacci(42) << endl;
  auto toc = chrono::steady_clock::now();

  auto elapsed_time = chrono::duration<double>(toc - tic); // Here auto stands for chrono::duration<double>

  //cout << typeid(elapsed_time).name() << endl;

  cout << "Calculating sequence took" << endl;
  cout << "Nanoseconds: " << std::chrono::duration_cast<chrono::nanoseconds>(toc - tic).count() << endl;
  cout << "Microseconds: " << std::chrono::duration_cast<chrono::microseconds>(toc - tic).count() << endl;
  cout << "Milliseconds: " << std::chrono::duration_cast<chrono::milliseconds>(toc - tic).count() << endl;
  cout << "Seconds: " << std::chrono::duration_cast<chrono::seconds>(toc - tic).count() << endl;
  cout << "Minutes: " << std::chrono::duration_cast<chrono::minutes>(toc - tic).count() << endl;
  cout << "Hours: " << std::chrono::duration_cast<chrono::hours>(toc - tic).count() << endl;

  return 0;
}
