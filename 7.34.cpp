#include <iostream>
#include <string>
#include <vector>

using std::cin, std::cout, std::endl;
using std::string;
using std::vector;

class Screen {
 public:
  void dummy_fcn(pos height) {}

 private:
  pos cursor = 0;
  pos height = 0, width = 0;
  typedef std::string::size_type pos;
};

int main() {}
