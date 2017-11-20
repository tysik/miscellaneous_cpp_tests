#include <iostream>
#include <complex>
#include <algorithm>
#include <vector>

using namespace std;

auto twice = [](int &a)->int{ return a *= 2; };
auto printer = [](const auto b){ cout << b << endl; };

const int my_test = 7;

int main()
{
  auto a = 2;
  int result = [](int input)->int{ return input * input; }(twice(a));

  printer(result);
  printer(complex<double>(1, 2));

  vector<int> v(10);
  iota(v.begin(), v.end(), 12);
  for_each(v.begin(), v.end(), [](auto a){ cout << a << " "; });
  cout << endl;

  sort(v.begin(), v.end(), [](auto a, auto b){ return (a > b); });

  for_each(v.begin(), v.end(), [](auto a){ cout << a << " "; });
  cout << endl;

  [&] { cout << my_test << endl; } ();
  int my_val = 5;
  auto print_my_val = [&]{ cout << my_val << endl; };
  print_my_val();

  return 0;
}
