#include <iostream>
#include <future>
#include <vector>

using namespace std;

void called_from_async(int a)
{
  cout << "Async call " << a << endl;
}

int twice(int a)
{
  return 2 * a;
}

int main()
{
  future<void> result(async(called_from_async, 12));

  cout << "Main call" << endl;

  result.get();

  //

  future<int> result_int(async([](int a, int b){ return a + b; }, 2, 5));

  cout << result_int.get() << endl;

  //

  vector<future<int>> futures;
  for (int i = 0; i < 10; ++i)
    futures.push_back(async(twice, i));

  for (auto &f : futures)
    cout << f.get() << " ";
  cout << endl;

  return 0;
}
