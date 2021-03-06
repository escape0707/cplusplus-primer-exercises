#include <string>
#include <vector>
#include <iostream>
using std::cin, std::cout, std::endl;
using std::string;
using std::vector;

vector<int> v1;
vector<int> v2(10);
vector<int> v3(10, 42);
vector<int> v4{10};
vector<int> v5{10, 42};
vector<string> v6{10};
vector<string> v7{10, "hi"};

template <typename T>
void print(const vector<T> &v) {
  cout << v.size() << ": ";
  for (const T &i : v) {
    cout << i << ' ';
  }
  cout << endl;
}

int main() {
  print(v1);
  print(v2);
  print(v3);
  print(v4);
  print(v5);
  print(v6);
  print(v7);
}