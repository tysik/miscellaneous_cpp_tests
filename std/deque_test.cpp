#include <iostream>
#include <deque>
#include <typeinfo>
#include <algorithm>
#include <stdexcept>
#include <iomanip>

using namespace std;

auto print = [](auto &v){
  for_each(v.begin(), v.end(), [](auto d) { cout << d << " ";});
  cout << endl;
};

int main()
{
  // Constructors
  deque<int> dq1;
  cout << "Type of deque<int>: " << typeid(deque<int>).name() << endl;

  deque<int> dq2(dq1);
  print(dq2);

  deque<double> dq3(10);
  print(dq3);

  deque<double> dq4(5, 1.5);
  print(dq4);

  double array1[] = {1.1, 2.2, 3.3, 4.4, 5.5};
  deque<double> dq5(array1, array1 + 5);
  print(dq5);

  deque<double> my_dek(5, 8.1);

  my_dek.front() = 7.7;
  my_dek.at(3) = 2.23;
  my_dek.back() = 9.9;

  my_dek.push_back(-1.1);
  my_dek.push_front(-3.4);

  cout << "my_dek.size(): " << my_dek.size() << endl;
  cout << "my_dek.max_size(): " << my_dek.max_size() << endl;
  cout << "my_dek.empty(): " << boolalpha << my_dek.empty() << endl;

  for (size_t i = 0; i < my_dek.size() + 1; ++i) {
    cout << "Element " << i << " accessed with []: " << my_dek[i] << endl;

    try {
      cout << "Element " << i << " accessed with at(i): " << my_dek.at(i) << endl;
    }
    catch (out_of_range&) {
      cout << "**out of range exception accessing element " << i << " with at() **" << endl;
    }
  }

  my_dek.pop_back();
  my_dek.pop_front();
  print(my_dek);

  auto it = my_dek.insert(my_dek.begin(), 321.67);
  print(my_dek);
  cout << *it << endl;

  it = my_dek.erase(my_dek.end() - 2);
  print(my_dek);
  cout << *it << endl;

  double array2[] = {10.1, 20.2, 30.3};
  my_dek.assign(array2, array2 + 3);
  print(my_dek);

  my_dek.resize(2);
  print(my_dek);

  return 0;
}
