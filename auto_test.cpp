#include <iostream>
#include <vector>
#include <typeinfo>

// C++98
std::vector<int>& add_one_98(std::vector<int> &v)
{
  for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
    *it += 1;

  return v;
}

void multiply_by_two_98(std::vector<int> &v)
{
  for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
    *it *= 2;
}

void print_vec_98(const std::vector<int> &v)
{
  for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it)
    std::cout << *it << " ";
  std::cout << std::endl;
}

// C++11
std::vector<int>& add_one_11(std::vector<int> &v)
{
  for (auto &i : v)
    i += 1;

  return v;
}

void multiply_by_two_11(std::vector<int> &v)
{
  for (auto &i : v)
    i *= 2;
}

void print_vec_11(const std::vector<int> &v)
{
  for (auto i : v)
    std::cout << i << " ";
  std::cout << std::endl;
}

// C++14
auto& add_one_14(auto &v)
{
  for (auto &i : v)
    i += 1;

  return v;
}

void multiply_by_two_14(auto &v)
{
  for (auto &i : v)
    i *= 2;
}

void print_vec_14(auto &v)
{
  for (auto i : v)
    std::cout << i << " ";
  std::cout << std::endl;
}


auto i = 1;

auto my_function()
{
  return 5.0f;
}


int main()
{
  std::cout << typeid(i).name() << std::endl;
  std::cout << typeid(my_function).name() << std::endl;

  std::vector<int> my_vec_98 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  print_vec_98(my_vec_98);
  multiply_by_two_98(add_one_98(my_vec_98));
  print_vec_98(my_vec_98);

  std::vector<int> my_vec_11 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  print_vec_11(my_vec_11);
  multiply_by_two_11(add_one_11(my_vec_11));
  print_vec_11(my_vec_11);

  std::vector<int> my_vec_14 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  print_vec_14(my_vec_14);
  multiply_by_two_14(add_one_14(my_vec_14));
  print_vec_14(my_vec_14);

  return 0;
}
