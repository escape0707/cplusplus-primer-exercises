#include <iostream>
#include <string>
#include <vector>

using std::cin, std::cout, std::endl;
using std::string;
using std::vector;

double calc(double);
int count(const string &, char);
int sum(vector<int>::iterator, vector<int>::iterator, int);
vector<int> vec(10);

int main() {
  calc(23.4, 55.1); // error: too many arguments
  count("abcda", 'a');
  calc(66);
  sum(vec.begin(), vec.end(), 3.8);
}
